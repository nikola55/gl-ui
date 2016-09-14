#ifndef TEXTURE_H
#define TEXTURE_H
#include <GLES2/gl2.h>
#include <string>

namespace gl {

class Texture {

    Texture(const Texture &) { }

    Texture& operator=(const Texture &) { }

public:

    Texture(const std::string &fileName);

    ~Texture() {
        if(m_textureId)
            glDeleteTextures(1, &m_textureId);
    }

    GLuint getTextureId() { return m_textureId; }

    bool loaded() const { return m_textureId != 0; }

    void activate() { glActiveTexture(m_textureId); }

    GLuint width() const { return m_width; }

    GLuint height() const { return m_height; }

private:
    GLuint m_textureId;
    GLuint m_width;
    GLuint m_height;
};

}

#endif // TEXTURE_H
