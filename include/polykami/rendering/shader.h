//
// Created by niek on 2025/07/09.
//

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace polykami::rendering {

    class Shader {
    public:
        static Shader create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        ~Shader();

        // === non-copyable but moveable ===
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader(Shader&&) noexcept;
        Shader& operator=(Shader&&) noexcept;

        // === Utility ===
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w) const;
        void setMat4(const std::string& name, const glm::mat4& value) const;

        [[nodiscard]] unsigned int getShaderProgramID() const;

    private:
        Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

        // === Private Utility methods ===
        enum class ShaderType { Vertex, Fragment, Program };

        static std::string readFile(const std::string& filePath);
        static void checkCompilationStatus(unsigned int id, ShaderType shaderType);
        [[nodiscard]] GLint getUniformLocation(const std::string& name) const;

        unsigned int shaderProgramID;
    };

}  // polykami::rendering

#endif //SHADER_H
