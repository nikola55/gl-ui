#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <string>
#include <GLES2/gl2.h>

namespace gl {

class ShaderProgram {

    ShaderProgram(const ShaderProgram &);

    ShaderProgram& operator=(const ShaderProgram &);

    static GLuint loadShader(GLenum type, const char *shaderSrc);

public:

    ShaderProgram(const std::string vShader, const std::string fShader);

    virtual ~ShaderProgram() {
        if(m_programId != 0) {
            glDeleteProgram(m_programId);
        }
    }

    bool compiled() const { return m_programId != 0; }

    void enable() { glUseProgram(m_programId); }

    GLint attributeLocation(const std::string &key) {
        return glGetAttribLocation(m_programId, key.c_str());
    }

    GLint uniformLocation(const std::string &key) {
        return glGetUniformLocation(m_programId, key.c_str());
    }

private:
    GLint m_programId;
};

}
#endif // SHADER_PROGRAM_H
