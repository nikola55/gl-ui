#include "texture.h"
#include "ui_common.h"
#include "image_io.h"
#include <SDL2/SDL_image.h>
#include <stdexcept>

using std::runtime_error;

using gl::Texture;
using ui::byte;
using ui::image;

static GLenum getFormat(byte bitsPerSample) {
    GLenum format;
    switch(bitsPerSample) {
    case 24: format = GL_RGB; break;
    case 32: format = GL_RGBA; break;
    default: throw runtime_error("unsupported texture format");
    }
    return format;
}

Texture::Texture(const std::string &fileName) : m_textureId(0), m_width(0), m_height(0) {

    glGenTextures(1, &m_textureId);

    if(glGetError() != GL_NO_ERROR) {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, m_textureId);

    try {
        image img = native::loadFromFile(fileName);
        GLenum format = getFormat(img.bitsPerSample());
        m_width = img.width();
        m_height = img.height();
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, img.data());
        if(glGetError() != GL_NO_ERROR) {
            glDeleteTextures(1, &m_textureId);
            m_height = 0;
            m_width = 0;
            m_textureId = 0;
        }
    } catch (...) {
        glDeleteTextures(1, &m_textureId);
        m_height = 0;
        m_width = 0;
        m_textureId = 0;
    }
    if(m_textureId != 0) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

}
