#pragma once
#include "Shader.h"
namespace dGL {
    void Shader::InitV_F_Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        std::string vShader_code = getShaderCode(vertexPath);
        std::string fShader_code = getShaderCode(fragmentPath);
        const char* vShader = vShader_code.c_str();
        const char* fShader = fShader_code.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glCheckError();
        glShaderSource(vertex, 1, &vShader, NULL);
        glCheckError();
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glCheckError();
        glShaderSource(fragment, 1, &fShader, NULL);
        glCheckError();
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        glCheckError();
        // shader Program
        ID = glCreateProgram();
        glCheckError();
        glAttachShader(ID, vertex);
        glCheckError();
        glAttachShader(ID, fragment);
        glCheckError();
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        glDeleteShader(vertex);
        glCheckError();
        glDeleteShader(fragment);
        glCheckError();




    }
    void Shader::InitC_Shader(const std::string& computeShaderPath) {
        std::string cShader_code = getShaderCode(computeShaderPath);

        const char* cShader = cShader_code.c_str();
        // 2. compile shaders
        unsigned int compute;
        // vertex shader
        compute = glCreateShader(GL_COMPUTE_SHADER);
        glCheckError();
        glShaderSource(compute, 1, &cShader, NULL);
        glCheckError();
        glCompileShader(compute);
        checkCompileErrors(compute, "COMPUTE");

        // shader Program
        ID = glCreateProgram();
        glCheckError();
        glAttachShader(ID, compute);
        glCheckError();
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        glDeleteShader(compute);
        glCheckError();


    }

    std::string Shader::getShaderCode(const std::string& path) const {

        std::string code;
        std::ifstream file;

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            // open files
            file.open(path);
            std::stringstream shaderStream;
            // read file's buffer contents into streams
            shaderStream << file.rdbuf();
            // close file handlers
            file.close();
            // convert stream into string
            code = shaderStream.str();

        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;

        }
        return code;



    }
    void Shader::checkCompileErrors(unsigned int shader, std::string type) const {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            glCheckError();
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                glCheckError();
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
            else {
                std::cout << "SUCCESS::SHADER_COMPILATION" << std::endl;
            }

        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            glCheckError();
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                glCheckError();
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
            else {
                std::cout << "SUCCESS::SHADER_LINKING" << std::endl;
            }
        }
    }

}