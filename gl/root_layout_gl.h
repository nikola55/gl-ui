#ifndef ROOT_LAYOUT_GL_H
#define ROOT_LAYOUT_GL_H
#include "context_egl.h"
#include "rectangle_base_layout.h"

namespace gl {

class RootLayout_GL : public ui::RectangleBaseLayout {

    RootLayout_GL(uint width, uint height);
    RootLayout_GL(const RootLayout_GL &) : m_EGLContext(0, 0) { }
    RootLayout_GL& operator=(const RootLayout_GL &) { }

public:

    virtual ~RootLayout_GL();

    void draw();

    void addChild(ui::shared_ptr<ui::View> chld);
    ui::shared_ptr<View> getChild(uint idx) const {
        if(idx == 0) {
            return m_rootView;
        } else {
            return 0;
        }
    }
    void removeChild(ui::shared_ptr<ui::View> chld);
    ui::uint childrenCount() const;

    static ui::shared_ptr<RootLayout_GL> create(uint w, uint h);

private:
    ui::mat3 T;
    ui::shared_ptr<ui::View> m_rootView;
    Context_EGL m_EGLContext;
};

}

#endif // ROOT_LAYOUT_GL_H
