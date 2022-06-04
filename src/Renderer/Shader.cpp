/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#include <Renderer/Shader.h>

namespace DT
{
    Shader::~Shader()
    {
        glDeleteProgram(id);
    }

    void Shader::Load(const char *vertexPath, const char *fragmentPath)
    {
        FT("Shader::Load()");

        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // close file handlers
            vShaderFile.close();
            fShaderFile.close();

            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure &e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");

        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");

        // shader Program
        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        CheckCompileErrors(id, "PROGRAM");

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::Use()
    {
        FT("Shader::Use()");

        glUseProgram(id);
    }

    void Shader::SetBool(const std::string &name, bool value) const
    {
        FT("Shader::SetBool()");

        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
    }

    void Shader::SetInt(const std::string &name, int value) const
    {
        FT("Shader::SetInt()");

        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void Shader::SetFloat(const std::string &name, float value) const
    {
        FT("Shader::SetFloat()");

        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

    void Shader::CheckCompileErrors(unsigned int shader, std::string type)
    {
        FT("Shader::CheckCompileErrors()");

        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

    void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
    {
        FT("Shader::SetVec2()");

        glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec2(const std::string &name, float x, float y) const
    {
        FT("Shader::SetVec2()");

        glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
    }

    void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
    {
        FT("Shader::SetVec3()");

        glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec3(const std::string &name, float x, float y, float z) const
    {
        FT("Shader::SetVec3()");

        glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
    }

    void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
    {
        FT("Shader::SetVec4()");

        glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec4(const std::string &name, float x, float y, float z, float w)
    {
        FT("Shader::SetVec4()");

        glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
    }

    void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
    {
        FT("Shader::SetMat2()");

        glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
    {
        FT("Shader::SetMat3()");

        glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
    {
        FT("Shader::SetMat4()");

        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
}