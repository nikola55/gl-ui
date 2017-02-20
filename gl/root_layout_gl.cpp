#include <GLES2/gl2.h>
#include "root_layout_gl.h"
#include "drawable_gl.h"

using gl::RootLayout_GL;
using gl::Context_EGL;
using gl::Drawable_GL;

using ui::View;
using ui::RectangleBaseLayout;
using ui::shared_ptr;
using ui::uint;
using ui::point;
using ui::mat3;
using ui::eye3x3;

RootLayout_GL::RootLayout_GL(uint w, uint h) : m_EGLContext(w, h) {

    point pos = { 0, 0 };
    position(pos);
    width(w);
    height(h);
    margin(0);
    padding(0);

    T(0,0) = 2.0/w; T(0, 1) = 0.0; T(0, 2) = -1.0;
    T(1,0) = 0.0; T(1, 1) = 2.0/h; T(1, 2) = -1.0;
    T(2,0) = 0.0; T(2, 1) = 0.0; T(2,2) = 1.0;

    glEnable(GL_SCISSOR_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Drawable_GL::initAuxiliaryFrameBuffer();

}

RootLayout_GL::~RootLayout_GL() {
    Drawable_GL::destroyAuxiliaryFrameFuffer();
}

shared_ptr<RootLayout_GL> RootLayout_GL::create(uint w, uint h) {
    return new RootLayout_GL(w,h);
}

void RootLayout_GL::addChild(View* chld) {
    if(childrenCount()==0) {
        RectangleBaseLayout::addChild(chld);
    }
}

void RootLayout_GL::draw() {

    static mat3 transl, transf;

    if(childrenCount() == 0) {
        return;
    }

    View* rootView = getChild(0);

    point pos = rootView->position();
    if(rootView->changed()) {
        if(Drawable_GL *drawable = dynamic_cast<Drawable_GL*>(rootView)) {
            eye3x3(transl);
            transl(0,2) = pos.x;
            transl(1,2) = pos.y;
            transf = T*transl;
            drawable->transform(transf);
            glViewport(0, 0, width(), height());
            rootView->draw();
            eglSwapBuffers(m_EGLContext.getDisplay(), m_EGLContext.getSurface());
        }
    }
}
