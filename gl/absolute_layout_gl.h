#ifndef ABSOLUTELAYOUT_GL_H
#define ABSOLUTELAYOUT_GL_H

#include "absolute_layout.h"
#include "drawable_gl.h"

namespace gl {

class AbsoluteLayout_GL : public ui::AbsoluteLayout, public Drawable_GL {
public:

    AbsoluteLayout_GL() : T(3,3) { }

    void transform(ui::mat);

    ui::mat transform();

    void draw();

private:
    ui::mat T;
};

}

#endif // ABSOLUTELAYOUT_GL_H
