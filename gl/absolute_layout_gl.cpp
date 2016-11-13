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

void AbsoluteLayout_GL::draw() {

    std::list<shared_ptr<View> >::iterator childrenIter = m_children.begin();

    static mat3 transl, transf;
    eye3x3(transl);

    for(; childrenIter != m_children.end() ; childrenIter++) {
        View *currChild = *childrenIter;
        if(Drawable_GL *drawable = dynamic_cast<Drawable_GL*>(currChild)) {

            point pos = currChild->position();
            uint w = currChild->width();
            uint h = currChild->height();

            trans3x3(transl, pos.x, pos.y);
            transf = T*transl;
            drawable->transform(transf);
            currChild->draw();
        }
    }

}


