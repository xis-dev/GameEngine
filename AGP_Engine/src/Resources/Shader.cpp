//
// Created by seer on 11/23/26.
//

#include "../../include/AGP_Engine/Resources/Shader.h"

#include <fstream>
#include <sstream>

#include "glad/glad.h"


namespace AGPEngine {
    Shader::~Shader() {
        Shader::destroy();
    }

    Shader::Shader(const std::string &vert, const std::string &frag) {

        m_handle = glCreateProgram();
        auto vertSrc = getShaderSource(vert);
        auto fragSrc = getShaderSource(frag);

        GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertID, 1, reinterpret_cast<const GLchar * const *>(vertSrc.c_str()), nullptr);
        glShaderSource(fragID, 1, reinterpret_cast<const GLchar * const *>(fragSrc.c_str()), nullptr);

        glCompileShader(vertID);

        char infoLog[512];
        int success;

        // Vert shader compilation error checking
        glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertID, 512, nullptr, infoLog);
            std::cerr << "Failed to compile vert shader: " << infoLog << "\n";
            return;
        }

        // frag shader compilation error checking
        glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(fragID, 512, nullptr, infoLog);
            std::cerr << "Failed to compile frag shader: " << infoLog << "\n";
            return;
        }

        glAttachShader(m_handle, vertID);
        glAttachShader(m_handle, fragID);

        glLinkProgram(m_handle);

        glGetProgramiv(m_handle, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(m_handle, 512, nullptr, infoLog);
            std::cerr << "Failed to link shader program: " << infoLog << "\n";
            return;
        }

        glDeleteShader(vertID);
        glDeleteShader(fragID);

    }

    void Shader::destroy() {
        if (m_handle != InvalidHandle) {
            glDeleteProgram(m_handle);
        }
    }

    std::string Shader::getShaderSource(const std::string &file) {

        std::ifstream stream{file};

        if (!stream.is_open()) {
            std::cerr << "AGP_ENGINE::SHADER: Failed to load shader file: " << file.c_str() << "\n";
            return {};
        }

        std::stringstream outSrc;
        outSrc << stream.rdbuf();
        stream.close();

        return outSrc.str();
    }
}
