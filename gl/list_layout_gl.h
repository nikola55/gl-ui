#ifndef LIST_LAYOUT_GL_H
#define LIST_LAYOUT_GL_H
#include "drawable_gl.h"
#include "list_layout.h"

namespace gl {

class ListLayout_GL : public ui::ListLayout, public Drawable_GL {

public:

    ListLayout_GL(bool);

    void draw();

    void transform(ui::mat3);

    ui::mat3 transform();

private:
    ui::mat3 T;
};

}

#endif // LIST_LAYOUT_GL_H
