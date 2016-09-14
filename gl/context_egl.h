#ifndef CONTEXT_EGL_H
#define CONTEXT_EGL_H
#include <EGL/egl.h>
#include "window.h"

namespace gl {

class Context_EGL {

private:

    Context_EGL(const Context_EGL&);

    Context_EGL& operator=(const Context_EGL&);

public:

    Context_EGL(unsigned width, unsigned height);

    ~Context_EGL();

    EGLDisplay getDisplay() {
        return m_display;
    }

    EGLSurface getSurface() {
        return m_surface;
    }

    EGLContext getContext() {
        return m_context;
    }

private:

    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;

    static const EGLint s_eglAttributes[];
    static const EGLint s_eglContextAttributes[];

    native::Window* m_Window;

};
}
#endif // CONTEXT_EGL_H
