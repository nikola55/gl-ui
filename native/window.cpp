#include "window.h"
#include <string.h>
#include <stdexcept>

#ifdef USE_X
#include <X11/Xlib.h>
#endif

using std::runtime_error;

#ifdef USE_X

class Window_X : public native::Window {

public:

    Window_X(unsigned width, unsigned height, const std::string &title) {
        m_display = XOpenDisplay(0);
        if(m_display == 0) {
            throw runtime_error("cannot open X display");
        }
        ::Window root = DefaultRootWindow(m_display);
        XSetWindowAttributes swa;
        swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;
        m_window = XCreateWindow(m_display, root, 0, 0, width, height, 0, CopyFromParent, InputOutput, CopyFromParent, CWEventMask, &swa);
        XSetWindowAttributes xAttr;
        xAttr.override_redirect = 0;
        XChangeWindowAttributes(m_display, m_window, CWOverrideRedirect, &xAttr);
        XWMHints hints;
        hints.input = 1;
        hints.flags = InputHint;
        XSetWMHints(m_display, m_window, &hints);

        XMapWindow(m_display, m_window);
        XStoreName(m_display, m_window, title.c_str());

        Atom wmState = XInternAtom(m_display, "_NET_WM_STATE", 0);
        XEvent xEv;
        memset(&xEv, 0, sizeof(xEv));
        xEv.type = ClientMessage;
        xEv.xclient.window = m_window;
        xEv.xclient.message_type = wmState;
        xEv.xclient.format = 32;
        xEv.xclient.data.l[0] = 1;
        xEv.xclient.data.l[1] = 0;
        XSendEvent(m_display, m_window, 0, SubstructureNotifyMask, &xEv);
    }

    ~Window_X() {
        XDestroyWindow(m_display, m_window);
        XCloseDisplay(m_display);
    }

    EGLNativeDisplayType getDisplay() {
        return static_cast<EGLNativeDisplayType>(m_display);
    }

    EGLNativeWindowType getWindow() {
        return static_cast<EGLNativeWindowType>(m_window);
    }

private:
    Display *m_display;
    ::Window m_window;
};

#endif

native::Window* native::Window::createNew(unsigned width, unsigned height) {

#ifdef USE_X
    return new Window_X(width, height, "");
#endif

}

void native::Window::destroy(Window *w) {
    delete w;
}


