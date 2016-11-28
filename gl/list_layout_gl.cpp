#include "list_layout_gl.h"

using gl::ListLayout_GL;
using gl::Drawable_GL;

using ui::ListLayout;
using ui::shared_ptr;
using ui::uint;
using ui::point;
using ui::mat3;
using ui::eye3x3;

ListLayout_GL::ListLayout_GL(bool horizontal) : ListLayout(horizontal) {
    eye3x3(T);
}

void ListLayout_GL::draw() {

    bool redraw = false;
    if(changed()) {
        redraw = true;
    } else {
        for(uint i = 0 ; i < childrenCount() ; i++) {
            View *cv = getChild(i);
            if(cv->changed()) {
                redraw = true;
                break;
            }
        }
    }

    if(redraw) {
        if(horizontal()) {
            draw_horizontal();
        } else {
            draw_vertical();
        }
    }

    changed(false);
}

void ListLayout_GL::draw_horizontal() {
    uint offset = 0;
    static mat3 translate, transform;
    eye3x3(translate);
    float tx, ty;
    uint pad = padding();
    for(uint i = 0 ; i < childrenCount() ; i++) {
        View *cv = getChild(i);
        Drawable_GL *cd = dynamic_cast<Drawable_GL*>(cv);
        tx = offset + pad;
        ty = pad;
        offset+= pad + cv->width();
        translate(0,2)=tx;
        translate(1,2)=ty;
        transform = T*translate;
        cd->transform(transform);
        cv->draw();
    }
}

void ListLayout_GL::draw_vertical() {
    uint offset = 0;
    static mat3 translate, transform;
    eye3x3(translate);
    float tx, ty;
    uint pad = padding();
    for(uint i = 0 ; i < childrenCount() ; i++) {
        View *cv = getChild(i);
        Drawable_GL *cd = dynamic_cast<Drawable_GL*>(cv);
        tx = pad;
        ty = offset + pad;
        offset += pad + cv->height();
        translate(0,2)=tx;
        translate(1,2)=ty;
        transform = T*translate;
        cd->transform(transform);
        cv->draw();
    }
}
