#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include <GLES2/gl2.h>
#include <ui_common.h>

namespace gl {

template <class Type> class VertexBuffer {

    VertexBuffer(const VertexBuffer &);

    VertexBuffer& operator&(const VertexBuffer &);

public:

    VertexBuffer(const Type *buf, unsigned bufSz);

    virtual ~VertexBuffer();

    GLuint getId() { return m_bufferId; }

    bool created() const { return m_bufferId != 0; }

    static ui::shared_ptr<VertexBuffer> getSquareTexCoord();

    static ui::shared_ptr<VertexBuffer> getRect3(ui::uint w, ui::uint h);

    static ui::shared_ptr<VertexBuffer> create(const Type *buf, unsigned bufSz);

private:
    GLuint m_bufferId;
};

}

#endif // VERTEX_BUFFER_H
