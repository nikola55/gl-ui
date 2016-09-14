#include "shader_program.h"
#include <vector>

using gl::ShaderProgram;

ShaderProgram::ShaderProgram(const std::string vShader, const std::string fShader) : m_programId(0) {
    GLuint vShaderId = loadShader(GL_VERTEX_SHADER, vShader.c_str());
    if(vShaderId == 0) {
        return;
    }
    GLuint fShaderId = loadShader(GL_FRAGMENT_SHADER, fShader.c_str());
    if(fShaderId == 0) {
        glDeleteShader(vShaderId);
        return;
    }
    m_programId = glCreateProgram();
    if(m_programId == 0) {
        glDeleteShader(vShaderId);
        glDeleteShader(fShaderId);
        return;
    }
    glAttachShader(m_programId, vShaderId);
    glAttachShader(m_programId, fShaderId);
    glLinkProgram(m_programId);

    GLint linked;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &linked);
    if(linked == 0) {
        GLint logLen;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &logLen);
        std::vector<char> statusStr(logLen+1, 0);
        glGetProgramInfoLog(m_programId, logLen, 0, &statusStr[0]);
        printf("link status %s\n", &statusStr[0]);
        glDeleteProgram(m_programId);
        m_programId = 0;
    }

    glDeleteShader(vShaderId);
    glDeleteShader(fShaderId);
}

GLuint ShaderProgram::loadShader(GLenum type, const char *shaderSrc) {

    GLuint shader = glCreateShader(type);
    if (shader == 0) {
        return 0;
    }
    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            std::vector<char> err(infoLen + 1, 0);
            glGetShaderInfoLog(shader, infoLen, NULL, &err[0]);
            printf("Error compiling shader:\n%s\n", &err[0]);
        }
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}
