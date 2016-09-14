#include "context_egl.h"
#include "window.h"
#include <stdexcept>

using gl::Context_EGL;
using std::runtime_error;
using native::Window;

Context_EGL::Context_EGL(unsigned width, unsigned height) :
    m_Window(native::Window::createNew(width, height)) {

    m_display = eglGetDisplay(m_Window->getDisplay());
    if(m_display == EGL_NO_DISPLAY) {
        native::Window::destroy(m_Window);
        throw runtime_error("cannot obtain display");
    }
    EGLint major, minor;
    if(!eglInitialize(m_display, &major, &minor)) {
        eglTerminate(m_display);
        native::Window::destroy(m_Window);
        throw runtime_error("cannot initialize EGL");
    }
    EGLConfig configs;
    EGLint numConfigs;
    if(!eglChooseConfig(m_display, s_eglAttributes, &configs, 1, &numConfigs)) {
        eglTerminate(m_display);
        native::Window::destroy(m_Window);
        throw runtime_error("cannot choose EGL config");
    }
    m_surface = eglCreateWindowSurface(m_display, configs, m_Window->getWindow(), 0);
    if(m_surface == EGL_NO_SURFACE) {
        eglTerminate(m_display);
        native::Window::destroy(m_Window);
        throw runtime_error("cannot create EGL surface");
    }
    m_context = eglCreateContext(m_display, configs, EGL_NO_CONTEXT, s_eglContextAttributes);
    if(m_context == EGL_NO_CONTEXT) {
        eglDestroySurface(m_display, m_surface);
        eglTerminate(m_display);
        native::Window::destroy(m_Window);
        throw runtime_error("cannot create EGL context");
    }
    if(!eglMakeCurrent(m_display, m_surface, m_surface, m_context)) {
        eglDestroyContext(m_display, m_context);
        eglDestroySurface(m_display, m_surface);
        eglTerminate(m_display);
        native::Window::destroy(m_Window);
        throw runtime_error("cannot create EGL context");
    }

}

Context_EGL::~Context_EGL() {
    eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(m_display, m_context);
    eglDestroySurface(m_display, m_surface);
    eglTerminate(m_display);
    native::Window::destroy(m_Window);
}

const EGLint Context_EGL::s_eglAttributes[] = {
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_RED_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,
    EGL_ALPHA_SIZE, 8,
    EGL_DEPTH_SIZE, 8,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    EGL_NONE
};

const EGLint Context_EGL::s_eglContextAttributes[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};
