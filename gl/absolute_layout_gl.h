#ifndef ABSOLUTELAYOUT_GL_H
#define ABSOLUTELAYOUT_GL_H

#include "absolute_layout.h"
#include "drawable_gl.h"

namespace gl {

class AbsoluteLayout_GL : public ui::AbsoluteLayout, public Drawable_GL {
public:

    AbsoluteLayout_GL() { }

    void transform(ui::mat3);

    ui::mat3 transform();

    void draw();

private:
    ui::mat3 T;
};

}

#endif // ABSOLUTELAYOUT_GL_H
