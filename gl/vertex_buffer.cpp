#include "vertex_buffer.h"

using gl::VertexBuffer;
using ui::shared_ptr;
using ui::uint;

static const GLfloat sq_tex_coord[] = {
    0.0, 1.0,
    1.0, 1.0,
    1.0, 0.0,
    0.0, 0.0
};

namespace gl {

template < > shared_ptr<VertexBuffer<GLfloat> > VertexBuffer<GLfloat>::getSquareTexCoord() {
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
