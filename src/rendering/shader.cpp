//
// Created by niek on 2025/07/09.
//

#include "polykami/rendering/shader.h"
#include <glad/glad.h>

#include <format>
#include <string>

#include <fstream>
#include <sstream>

#include <iostream>
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
            checkCompilationStatus(vertex, ShaderType::Vertex);

            const unsigned int fragment{ glCreateShader(GL_FRAGMENT_SHADER) };
            glShaderSource(fragment, 1, &fShaderCode, nullptr);
            glCompileShader(fragment);
            checkCompilationStatus(fragment, ShaderType::Fragment);

            // === create and link program
            shaderProgramID = { glCreateProgram() };
            glAttachShader(shaderProgramID, vertex);
            glAttachShader(shaderProgramID, fragment);
            glLinkProgram(shaderProgramID);
            checkCompilationStatus(shaderProgramID, ShaderType::Program);

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
            throw std::runtime_error(std::format("Shader file not found: {}", filePath));
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

    void Shader::checkCompilationStatus(const unsigned int id, const ShaderType shaderType) {
        GLint success;
        constexpr size_t LOG_SIZE{ 512 };
        char infoLog[LOG_SIZE];

        switch (shaderType) {
            // retrieve compilation status
            case ShaderType::Vertex:
            case ShaderType::Fragment: {
                glGetShaderiv(id, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glGetShaderInfoLog(id, LOG_SIZE, nullptr, infoLog);
                    const char* typeStr = shaderType == ShaderType::Vertex ? "Vertex" : "Fragment";
                    const std::string msg = std::format("Shader compilation failed ({}): {}", typeStr, infoLog);
                    throw std::runtime_error(msg);
                }
                break;
            }

            // retrieve linking status
            case ShaderType::Program: {
                glGetProgramiv(id, GL_LINK_STATUS, &success);
                if (!success) {
                    glGetProgramInfoLog(id, LOG_SIZE, nullptr, infoLog);
                    const std::string msg = std::format("Shader link failed: {}", infoLog);
                    throw std::runtime_error(msg);
                }
                break;
            }

            // notify user there's an unsupported shader
            default:
                std::cerr << "Unsupported shader type." << '\n';
        }
    }

    int Shader::getUniformLocation(const std::string &name) const {
        return glGetUniformLocation(shaderProgramID, name.c_str());
    }

    // === Start of setting uniform properties ===
    void Shader::setInt(const std::string &name, const int value) const {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::setFloat(const std::string &name, const float value) const {
        glUniform1f(getUniformLocation(name), value);
    }

    void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2f(getUniformLocation(name), value.x, value.y);
    }

    void Shader::setVec2(const std::string &name, const float x, const float y) const {
        glUniform2f(getUniformLocation(name), x, y);
    }

    void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::setVec3(const std::string &name, const float x, const float y, const float z) const {
        glUniform3f(getUniformLocation(name), x, y, z);
    }

    void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
        glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::setVec4(const std::string &name, const float x, const float y, const float z, const float w) const {
        glUniform4f(getUniformLocation(name), x, y, z, w);
    }

    void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
    }
    // === End of setting uniform properties ===

}  // polykami::rendering