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

RootLayout_GL::RootLayout_GL(uint width, uint height) : m_EGLContext(width, height) {

    point pos = { 0, 0 };
    this->position(pos);
    this->width(width);
    this->height(height);
    this->margin(0);
    this->padding(0);

    T(0,0) = 2.0/float(width); T(0, 1) = 0.0; T(0, 2) = -1.0;
    T(1,0) = 0.0; T(1, 1) = 2.0/float(height); T(1, 2) = -1.0;
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
    m_rootView = chld;
}

void RootLayout_GL::removeChild(View* chld) {
    View *root = m_rootView;
    if(dynamic_cast<void*>(root) == dynamic_cast<void*>(chld)) {
        m_rootView = 0;
    }
}

uint RootLayout_GL::childrenCount() const {
    return 1;
}

void RootLayout_GL::draw() {

    if(m_rootView == 0) {
        return;
    }

    point pos = m_rootView->position();

    View* rootView = m_rootView;
    if(rootView->changed()) {
        Drawable_GL *drawable = dynamic_cast<Drawable_GL*>(rootView);
        static mat3 transl, transf;
        eye3x3(transl);
        transl(0,2) = pos.x;
        transl(1,2) = pos.y;
        transf = T*transl;
        drawable->transform(transf);
        glViewport(0, 0, width(), height());
        m_rootView->draw();
        eglSwapBuffers(m_EGLContext.getDisplay(), m_EGLContext.getSurface());
    }
}
