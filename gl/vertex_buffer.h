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

    static ui::shared_ptr<VertexBuffer> create(const _Type *buf, unsigned bufSz);

};

}

#endif // VERTEX_BUFFER_H
