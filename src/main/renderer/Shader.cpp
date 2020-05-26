/**
 * @file Shader.cpp
 * @brief Implements a shader
 * @author Samuel Gauthier
 * @version 0.1.0
 * @date 2018-11-21
 */
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <GL/glew.h>

#include "Shader.h"

#include "utils/Utils.h"
#include "utils/Logger.h"

namespace iphito::renderer {

using namespace iphito::utils;

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {

    if(!Utils::isGlfwInitialized())
        throw std::runtime_error("Please initialize GLFW.");

    if(!Utils::isGlewInitialized())
        throw std::runtime_error("Please initialize Glew.");
    

    this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexShaderCode = Utils::readFile(vertexShaderPath);
    std::string fragmentShaderCode = Utils::readFile(fragmentShaderPath);

    this->compileShader(vertexShaderID, vertexShaderCode, "vertex shader (" +
                        vertexShaderPath + ")");
    this->compileShader(fragmentShaderID, fragmentShaderCode, "fragment shader"
                        " (" + fragmentShaderPath + ")");

    Logger::Instance()->info("Linking program");

    this->shaderProgramID = glCreateProgram();
    glAttachShader(this->shaderProgramID, this->vertexShaderID);
    glAttachShader(this->shaderProgramID, this->fragmentShaderID);
    glLinkProgram(this->shaderProgramID);


    GLint linkStatus = 0;
    int infoLogLength = 0;

    glGetProgramiv(this->shaderProgramID, GL_LINK_STATUS, &linkStatus);
    glGetProgramiv(this->shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if(infoLogLength > 0) {

        std::vector<char> shaderErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(this->shaderProgramID, infoLogLength, NULL,
                            &shaderErrorMessage[0]);
        std::stringstream errorMessage;
        std::copy(shaderErrorMessage.begin(), shaderErrorMessage.end(),
                  std::ostream_iterator<char>(errorMessage, ""));
        
        if(linkStatus == GL_FALSE)
            throw std::runtime_error(errorMessage.str());
        else
            Logger::Instance()->critical(errorMessage.str());
    }

    glDetachShader(this->shaderProgramID, this->vertexShaderID);
    glDetachShader(this->shaderProgramID, this->fragmentShaderID);

    glDeleteShader(this->vertexShaderID);
    glDeleteShader(this->fragmentShaderID);
}

Shader::~Shader() {

    /* glDetachShader(this->shaderProgramID, this->vertexShaderID); */
    /* glDetachShader(this->shaderProgramID, this->fragmentShaderID); */

    /* glDeleteShader(this->vertexShaderID); */
    /* glDeleteShader(this->fragmentShaderID); */
}

void Shader::setMatrix4(const std::string& name,
                        const Eigen::Matrix4d& matrix) {

    int matrixLocation = glGetUniformLocation(this->shaderProgramID,
                                              name.c_str());
    Eigen::Matrix4f m = matrix.cast<float>();
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, m.data());
}

GLuint Shader::getProgramID() {

    return this->shaderProgramID;
}

void Shader::useProgram() {

    glUseProgram(this->shaderProgramID);
}

void Shader::compileShader(GLuint& shaderID, std::string& shaderCode, 
                           std::string logInfo) {

    Logger::Instance()->info("Compiling shader: " + logInfo);

    const char* shaderSource = shaderCode.c_str();
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    /* std::unique_ptr<const char[]> shaderSource(shaderCode.c_str()); */
    /* glShaderSource(shaderID, 1, shaderSource.get(), NULL); */
    glCompileShader(shaderID);

    GLint compileStatus = 0;
    int infoLogLength = 0;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if(infoLogLength > 0) {

        std::vector<char> shaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL,
                           &shaderErrorMessage[0]);
        std::stringstream errorMessage;
        std::copy(shaderErrorMessage.begin(), shaderErrorMessage.end(),
                  std::ostream_iterator<char>(errorMessage, ""));

        if(compileStatus == GL_FALSE)
            throw std::runtime_error(errorMessage.str());
        else
            Logger::Instance()->critical(errorMessage.str());
    }

}

} /* namespace iphito::renderer */
