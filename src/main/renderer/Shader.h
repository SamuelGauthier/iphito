/**
 * @file Shader.h
 * @brief Describes a Shader
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-11-21
 */

#ifndef SHADER_H
#define SHADER_H value

#include <string>
#include <GL/glew.h>

class Shader {

public:

    Shader() = delete;
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    ~Shader();

    GLuint getProgramID();
    
private:

    GLuint shaderProgramID;
    GLuint vertexShaderID;
    GLuint fragmentShaderID;

    std::string vertexShaderPath;
    std::string fragmentShaderPath;

    void compileShader(GLuint& shaderID, std::string& shaderCode,
                       std::string logInfo = "");
};

#endif /* ifndef SHADER_H */
