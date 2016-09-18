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
using ui::mat;
using ui::eye3x3;

RootLayout_GL::RootLayout_GL(uint width, uint height) : T(3, 3), m_EGLContext(width, height) {

    point pos = { 0, 0 };
    this->position(pos);
    this->width(width);
    this->height(height);
    this->margin(0);
    this->padding(0);

    T(0,0) = 2.0/float(width); T(0, 1) = 0.0; T(0, 2) = -1.0;
    T(1,0) = 0.0; T(1, 1) = 2.0/float(height); T(1, 2) = -1.0;
    T(2,0) = 0.0; T(2, 1) = 0.0; T(2,2) = 1.0;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_SCISSOR_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

RootLayout_GL::~RootLayout_GL() {

}

shared_ptr<RootLayout_GL> RootLayout_GL::create(uint w, uint h) {
    return new RootLayout_GL(w,h);
}

void RootLayout_GL::addChild(shared_ptr<View> chld) {
    m_RootView = chld;
}

void RootLayout_GL::removeChild(shared_ptr<View> chld) {
    View *root = m_RootView;
    if(root == chld) {
        m_RootView = shared_ptr<View>(0);
    }
}

uint RootLayout_GL::childrenCount() const {
    return 1;
}

void RootLayout_GL::draw() {

    if(m_RootView == 0) {
        return;
    }

    glViewport(0, 0, width(), height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    point pos = m_RootView->position();
    uint w = m_RootView->width();
    uint h = m_RootView->height();

    Drawable_GL &drawable = dynamic_cast<Drawable_GL&>(*m_RootView);

    mat TranslateChild(3,3);
    eye3x3(TranslateChild);
    TranslateChild(0,2) = pos.x;
    TranslateChild(1,2) = pos.y;
    mat TransformChild = T*TranslateChild;

    drawable.transform(TransformChild);

    m_RootView->draw();

    eglSwapBuffers(m_EGLContext.getDisplay(), m_EGLContext.getSurface());
}
