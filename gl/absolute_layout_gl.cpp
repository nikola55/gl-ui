#include "absolute_layout_gl.h"
#include <GLES2/gl2.h>

using gl::Drawable_GL;
using gl::AbsoluteLayout_GL;

using ui::mat;
using ui::uint;
using ui::point;
using ui::shared_ptr;
using ui::eye3x3;
using ui::trans3x3;

void AbsoluteLayout_GL::transform(mat t) {
    T=t;
}

mat AbsoluteLayout_GL::transform() {
    return T;
}

void AbsoluteLayout_GL::draw() {

    std::list<shared_ptr<View> >::iterator childrenIter = m_Children.begin();

    for(; childrenIter != m_Children.end() ; childrenIter++) {
        View *currChild = *childrenIter;
        Drawable_GL *drawable = 0;
        if(drawable = dynamic_cast<Drawable_GL*>(currChild)) {

            point pos = currChild->position();
            uint w = currChild->width();
            uint h = currChild->height();
            glScissor(pos.x, pos.y, w, h);

            mat Translate(3,3);
            eye3x3(Translate);
            trans3x3(Translate, pos.x, pos.y);
            mat TransfChld = T*Translate;

            drawable->transform(TransfChld);
            currChild->draw();
        }
    }

}


