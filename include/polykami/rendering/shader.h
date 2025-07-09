//
// Created by niek on 2025/07/09.
//

#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace polykami::rendering {


    class Shader {
    public:
        static Shader create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        ~Shader();

        // === Utility ===
        [[nodiscard]] unsigned int getShaderProgramID() const;

    private:
        Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

        // === Compilation ===
        enum ShaderType { VERTEX, FRAGMENT, PROGRAM };
        static std::string readFile(const std::string& filePath);
        static void checkCompilationStatus(unsigned int id, ShaderType shaderType);

        unsigned int shaderProgramID;
    };

}  // polykami::rendering

#endif //SHADER_H
