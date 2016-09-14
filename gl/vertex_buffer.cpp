#include "vertex_buffer.h"

using gl::VertexBuffer;
using ui::shared_ptr;
using ui::uint;

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

static const GLfloat vertex_data[] = {
    -1.0, -1.0, 1.0,
    1.0, -1.0, 1.0,
    1.0, 1.0, 1.0,
    -1.0, 1.0, 1.0
};

//namespace gl {
//template <  >  VertexBuffer<GLfloat>& VertexBuffer<GLfloat>::getSquare3() {
//    static VertexBuffer gSquare3(vertex_data, sizeof(vertex_data));
//    return gSquare3;
//}
//}

static const GLfloat sq_tex_coord[] = {
    0.0, 1.0,
    1.0, 1.0,
    1.0, 0.0,
    0.0, 0.0
};

namespace gl {

template <  > shared_ptr<VertexBuffer<GLfloat> > VertexBuffer<GLfloat>::getSquareTexCoord() {
    return new VertexBuffer<GLfloat>(sq_tex_coord, sizeof(sq_tex_coord));
}

}

namespace gl {

template < > shared_ptr<VertexBuffer<GLfloat> > VertexBuffer<GLfloat>::getRect3(uint w, uint h) {

    GLfloat glw = w;
    GLfloat glh = h;
    GLfloat buf[] = {
        0.0, 0.0, 1.0,
        glw, 0.0, 1.0,
        glw, glh, 1.0,
        0.0, glh, 1.0
    };

    return new VertexBuffer<GLfloat>(buf, sizeof(buf));
}

}
