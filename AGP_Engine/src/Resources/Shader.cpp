//
// Created by seer on 11/23/26.
//

#include "../../include/AGP_Engine/Resources/Shader.h"

#include <expected>
#include <fstream>
#include <sstream>

#include "glad/glad.h"


namespace AGPEngine {
    Shader::~Shader() {
        Shader::destroy();
    }

    Shader::Shader(const std::string &vert, const std::string &frag) {

        auto vertSrc = GetShaderSource(vert);
        if (!vertSrc) {
            std::cerr << vertSrc.error().message << "\n";
            return;
        }
        auto fragSrc = GetShaderSource(frag);
        if (!fragSrc) {
            std::cerr << fragSrc.error().message << "\n";
            return;
        }

        m_handle = glCreateProgram();

        GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);

        const char* cVertSrc = vertSrc.value().c_str();
        const char* cFragSrc = fragSrc.value().c_str();

        glShaderSource(vertID, 1,  &cVertSrc, nullptr);
        glShaderSource(fragID, 1,  &cFragSrc, nullptr);

        char infoLog[512];
        int success;

        glCompileShader(vertID);
        // Vert shader compilation error checking
        glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertID, 512, nullptr, infoLog);
            std::cerr << "Failed to compile vert shader: " << infoLog << "\n";
            return;
        }

        glCompileShader(fragID);
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

    void Shader::use() const {
        glUseProgram(m_handle);
    }

    void Shader::destroy() {
        if (m_handle != InvalidHandle) {
            glDeleteProgram(m_handle);
            m_handle = InvalidHandle;
        }

    }

    std::expected<std::string, Error<Shader>> Shader::GetShaderSource(const std::string &file) {

        std::ifstream stream{file};
        stream.open(file);
        if (!stream.is_open()) {
            std::cerr << "AGP_ENGINE::SHADER: Failed to load shader file: " << file.c_str() << "\n";
            return std::unexpected(Error<Shader>{.message = "AGP_ENGINE: Failed to open shader file: " + file});
        }

        std::stringstream outSrc;
        outSrc << stream.rdbuf();
        stream.close();

        return outSrc.str();
    }
}
