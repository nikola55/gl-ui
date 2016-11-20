#ifndef ABSOLUTELAYOUT_GL_H
#define ABSOLUTELAYOUT_GL_H

#include "absolute_layout.h"
#include "drawable_gl.h"

namespace gl {

class AbsoluteLayout_GL : public ui::AbsoluteLayout, public Drawable_GL {
public:

    AbsoluteLayout_GL() { }

    void transform(const ui::mat3& t) { m_transform = t; }

    const ui::mat3& transform() const { return m_transform; }

    void draw();

protected:
    ui::mat3 m_transform;
};

}

#endif // ABSOLUTELAYOUT_GL_H
