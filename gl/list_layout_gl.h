#ifndef LIST_LAYOUT_GL_H
#define LIST_LAYOUT_GL_H
#include "drawable_gl.h"
#include "list_layout.h"

namespace gl {

class ListLayout_GL : public ui::ListLayout, public Drawable_GL {

public:

    ListLayout_GL(bool);

    void draw();

    void transform(const ui::mat3& t) {
        T = t;
        changed(true);
    }

    const ui::mat3& transform() const { return T; }

protected:

    void draw_vertical();

    void draw_horizontal();

private:
    ui::mat3 T;
};

}

#endif // LIST_LAYOUT_GL_H
