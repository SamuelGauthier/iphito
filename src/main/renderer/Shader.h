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
#include <eigen3/Eigen/Core>

namespace iphito::renderer {

class Shader {

public:

    Shader() = delete;
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    ~Shader();

    void setMatrix4(const std::string& name, const Eigen::Matrix4d& matrix);

    GLuint getProgramID();
    void useProgram();
    
private:

    GLuint shaderProgramID;
    GLuint vertexShaderID;
    GLuint fragmentShaderID;

    std::string vertexShaderPath;
    std::string fragmentShaderPath;

    void compileShader(GLuint& shaderID, std::string& shaderCode,
                       std::string logInfo = "");
};

} /* namespace iphito::renderer */

#endif /* ifndef SHADER_H */
