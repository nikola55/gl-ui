#include "list_layout_gl.h"

using gl::ListLayout_GL;
using gl::Drawable_GL;

using ui::ListLayout;
using ui::shared_ptr;
using ui::uint;
using ui::point;
using ui::mat;
using ui::eye3x3;

ListLayout_GL::ListLayout_GL(bool horizontal) : ListLayout(horizontal), T(3,3) {
    eye3x3(T);
}

void ListLayout_GL::transform(mat t) {
    T = t;
}

mat ListLayout_GL::transform() {
    return T;
}

void ListLayout_GL::draw() {

    std::list< shared_ptr< View > >::iterator chldIter = m_Children.begin();

    uint offset = 0;

    for(; chldIter != m_Children.end() ; chldIter++) {
        View *cv = *chldIter;
        if(Drawable_GL *cd = dynamic_cast<Drawable_GL*>(cv)) {
            float tx, ty, cvHeight, cvWidth;
            if(horizontal()) {
                tx = offset + padding();
                ty = padding();
                cvWidth = cv->width();
                cvHeight = cv->height();
                if(cvHeight > 2*padding()+height()) {
                    cvHeight = height()-padding();
                }
                offset+= padding() + cv->width();
            } else {
                tx = padding();
                ty = offset + padding();
                cvWidth = cv->width();
                cvHeight = cv->height();
                if(cvWidth > 2*padding()+width()) {
                    cvWidth = width()+padding();
                }
                offset += padding() + cv->height();
            }
            mat Translate(3,3);
            eye3x3(Translate);
            Translate(0,2)=tx;
            Translate(1,2)=ty;
            mat Transform = T*Translate;
            cv->width(cvWidth);
            cv->height(cvHeight);
            cd->transform(Transform);
            cv->draw();
        }
    }

}

