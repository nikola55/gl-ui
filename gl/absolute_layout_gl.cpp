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

    std::list<shared_ptr<View> >::iterator childrenIter = m_children.begin();

    bool redraw = false;
    if(changed()) {
        redraw = true;
    } else {
        for(; childrenIter != m_children.begin() ; childrenIter++) {
            View *currChild = *childrenIter;
            if(currChild->changed()) {
                redraw = true;
                break;
            }
        }
    }

    static mat3 transl, transf;
    eye3x3(transl);

    if(redraw) {
        childrenIter = m_children.begin();
        for(; childrenIter != m_children.end() ; childrenIter++) {
            View *currChild = *childrenIter;
            Drawable_GL *drawable = dynamic_cast<Drawable_GL*>(currChild);
            point pos = currChild->position();
            uint w = currChild->width();
            uint h = currChild->height();

            trans3x3(transl, pos.x, pos.y);
            transf = m_transform*transl;
            drawable->transform(transf);
            currChild->draw();
        }
    }

    RectangleBaseLayout::changed(false);

}


