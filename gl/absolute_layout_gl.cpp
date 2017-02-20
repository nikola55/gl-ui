#include "absolute_layout_gl.h"
#include <GLES2/gl2.h>
#include <typeinfo>

using gl::Drawable_GL;
using gl::AbsoluteLayout_GL;

using ui::mat3;
using ui::uint;
using ui::point;
using ui::shared_ptr;
using ui::eye3x3;
using ui::trans3x3;

void AbsoluteLayout_GL::draw() {

    bool redraw = false;
    if(changed()) {
        redraw = true;
    } else {
        for(uint i = 0 ; i < childrenCount() ; i++) {
            View *currChild = getChild(i);
            if(currChild->changed()) {
                redraw = true;
                break;
            }
        }
    }

    static mat3 transl, transf;
    eye3x3(transl);

    if(redraw) {
        for(uint i = 0 ; i < childrenCount() ; i++) {
            View* currChild = getChild(i);
            if(Drawable_GL *drawable = dynamic_cast<Drawable_GL*>(currChild)) {
                point pos = currChild->position();
                trans3x3(transl, pos.x, pos.y);
                transf = m_transform*transl;
                drawable->transform(transf);
                currChild->draw();
            }
        }
    }

    changed(false);

}


