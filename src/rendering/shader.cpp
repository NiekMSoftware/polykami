//
// Created by niek on 2025/07/09.
//

#include "polykami/rendering/shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <format>
#include <filesystem>

namespace polykami::rendering {

    Shader::Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) : shaderProgramID(0) {
        try {
            // === read files as code
            const std::string vertexCode = readFile(vertexShaderSource);
            const std::string fragmentCode = readFile(fragmentShaderSource);
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();

            // === create and compile shaders
            const unsigned int vertex{ glCreateShader(GL_VERTEX_SHADER) };
            glShaderSource(vertex, 1, &vShaderCode, nullptr);
            glCompileShader(vertex);
            checkCompilationStatus(vertex, VERTEX);

            const unsigned int fragment{ glCreateShader(GL_FRAGMENT_SHADER) };
            glShaderSource(fragment, 1, &fShaderCode, nullptr);
            glCompileShader(fragment);
            checkCompilationStatus(fragment, FRAGMENT);

            // === create and link program
            shaderProgramID = { glCreateProgram() };
            glAttachShader(shaderProgramID, vertex);
            glAttachShader(shaderProgramID, fragment);
            glLinkProgram(shaderProgramID);
            checkCompilationStatus(shaderProgramID, PROGRAM);

            // === delete redundant resources
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        } catch (const std::exception&) {
            // cleanup on failure
            if (shaderProgramID != 0) {
                glDeleteProgram(shaderProgramID);
            }
            throw;
        }

    }

    Shader::~Shader() {
        if (shaderProgramID != 0) {
            glDeleteProgram(shaderProgramID);
        }
    }

    Shader::Shader(Shader&& other) noexcept : shaderProgramID(other.shaderProgramID) {
        other.shaderProgramID = 0;
    }

    Shader& Shader::operator=(Shader&& other) noexcept {
        if (this != &other) {
            if (shaderProgramID != 0) {
                glDeleteProgram(shaderProgramID);
            }
            shaderProgramID = other.shaderProgramID;
            other.shaderProgramID = 0;
        }
        return *this;
    }

    Shader Shader::create(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) {
        return Shader{ vertexShaderSource, fragmentShaderSource };
    }

    unsigned int Shader::getShaderProgramID() const {
        return shaderProgramID;
    }

    std::string Shader::readFile(const std::string &filePath) {
        // ensure shader exists
        if (!std::filesystem::exists(filePath)) {
            std::cerr << std::format("Shader file not found: {}", filePath);
            return "";
        }

        // try to read the file
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            file.open(filePath);
            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();
            return buffer.str();
        } catch (std::ifstream::failure &e) {
            std::cerr << std::format("Failed to read shader file {}: {}\n", filePath, e.what()) << '\n';
            return "";
        }
    }

    void Shader::checkCompilationStatus(const GLuint id, const ShaderType shaderType) {
        GLint success;
        constexpr size_t LOG_SIZE{ 512 };
        char infoLog[LOG_SIZE];

        switch (shaderType) {
            // retrieve compilation status
            case VERTEX:
            case FRAGMENT: {
                glGetShaderiv(id, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glGetShaderInfoLog(id, LOG_SIZE, nullptr, infoLog);
                    const char* typeStr = shaderType == VERTEX ? "VERTEX" : "FRAGMENT";
                    std::cerr << std::format("Shader compilation failed ({}): {}", typeStr, infoLog).c_str() << '\n';
                }
                break;
            }

            // retrieve linking status
            case PROGRAM: {
                glGetProgramiv(id, GL_LINK_STATUS, &success);
                if (!success) {
                    glGetProgramInfoLog(id, LOG_SIZE, nullptr, infoLog);
                    std::cerr << std::format("Shader linking failed: {}", infoLog).c_str() << '\n';
                }
                break;
            }

            // notify user there's an unsupported shader
            default:
                std::cerr << "Unsupported shader type." << '\n';
        }
    }

}  // polykami::rendering