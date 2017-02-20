#ifndef ROOT_LAYOUT_GL_H
#define ROOT_LAYOUT_GL_H
#include "context_egl.h"
#include "rectangle_base_layout.h"

namespace gl {

class RootLayout_GL : public ui::RectangleBaseLayout {

    RootLayout_GL(uint w, uint h);

    RootLayout_GL(const RootLayout_GL &);
    RootLayout_GL& operator=(const RootLayout_GL &);

public:

    virtual ~RootLayout_GL();

    void draw();

    void addChild(ui::View* chld);

    static ui::shared_ptr<RootLayout_GL> create(uint w, uint h);

private:
    ui::mat3 T;
    Context_EGL m_EGLContext;
};

}

#endif // ROOT_LAYOUT_GL_H
