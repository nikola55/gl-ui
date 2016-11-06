#include "absolute_layout_gl.h"
#include <GLES2/gl2.h>

using gl::Drawable_GL;
using gl::AbsoluteLayout_GL;

using ui::mat3;
using ui::uint;
using ui::point;
using ui::shared_ptr;
using ui::eye3x3;
using ui::trans3x3;

void AbsoluteLayout_GL::transform(mat3 t) {
    T=t;
}

mat3 AbsoluteLayout_GL::transform() {
    return T;
}

void AbsoluteLayout_GL::draw() {

    std::list<shared_ptr<View> >::iterator childrenIter = m_children.begin();

    for(; childrenIter != m_children.end() ; childrenIter++) {
        View *currChild = *childrenIter;
        if(Drawable_GL *drawable = dynamic_cast<Drawable_GL*>(currChild)) {

            point pos = currChild->position();
            uint w = currChild->width();
            uint h = currChild->height();

            mat3 Translate;
            eye3x3(Translate);
            trans3x3(Translate, pos.x, pos.y);
            mat3 TransfChld = T*Translate;
            drawable->transform(TransfChld);
            currChild->draw();
        }
    }

}


