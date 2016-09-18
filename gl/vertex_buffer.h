#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include <GLES2/gl2.h>
#include <ui_common.h>

namespace gl {

template <class _Type> class VertexBuffer {

    GLuint m_bufferId;

    VertexBuffer(const VertexBuffer &) { }

    VertexBuffer& operator&(const VertexBuffer &) { }

public:

    VertexBuffer(const _Type *buf, unsigned bufSz);

    virtual ~VertexBuffer();

    GLuint getId() { return m_bufferId; }

    bool created() const { return m_bufferId != 0; }

    static ui::shared_ptr<VertexBuffer> getSquareTexCoord();

    static ui::shared_ptr<VertexBuffer> getRect3(ui::uint w, ui::uint h);

};

template < class _Type > VertexBuffer<_Type>::VertexBuffer(const _Type *buf, unsigned bufSz) : m_bufferId(0) {
    glGenBuffers(1, &m_bufferId);
    if(glGetError() != GL_NO_ERROR) {
        m_bufferId = 0;
        return;
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    glBufferData(GL_ARRAY_BUFFER, bufSz, buf, GL_STATIC_DRAW);
    if(glGetError() != GL_NO_ERROR) {
        glDeleteBuffers(1, &m_bufferId);
        m_bufferId = 0;
    }
}

template < class _Type > VertexBuffer<_Type>::~VertexBuffer() {
    if(m_bufferId != 0) {
        glDeleteBuffers(1, &m_bufferId);
        m_bufferId = 0;
    }
}

}

#endif // VERTEX_BUFFER_H
