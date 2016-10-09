#include "window.h"
#include <string.h>
#include <stdexcept>

using std::runtime_error;

#if defined(USE_X)
#include <X11/Xlib.h>
#include <X11/Xutil.h>

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
        return reinterpret_cast<EGLNativeDisplayType>(m_display);
    }

    EGLNativeWindowType getWindow() {
        return reinterpret_cast<EGLNativeWindowType>(m_window);
    }

private:
    Display *m_display;
    ::Window m_window;
};

#elif defined(RASPBERRY_PI)
#include <bcm_host.h>

struct BCM_Host {
    BCM_Host() {
        bcm_host_init();
    }
    ~BCM_Host() {
        bcm_host_deinit();
    }

} ;

class Window_BCM : public native::Window {

    static BCM_Host s_bcm_host;

    EGL_DISPMANX_WINDOW_T nativewindow;
    DISPMANX_DISPLAY_HANDLE_T dispman_handle;
    DISPMANX_ELEMENT_HANDLE_T dispman_element;


public:

    Window_BCM(unsigned width, unsigned height) {

        unsigned aWidth, aHeight;
        int success = graphics_get_display_size(0 /* LCD */, &aWidth, &aHeight);
        if(success < 0) {
            throw runtime_error("cannot obtain bcm size");
        }

        VC_RECT_T dst_rect;
        VC_RECT_T src_rect;
        dst_rect.x = 0;
        dst_rect.y = 0;
        dst_rect.width = aWidth;
        dst_rect.height = aHeight;
        src_rect.x = 0;
        src_rect.y = 0;
        src_rect.width = aWidth << 16;
        src_rect.height = aHeight << 16;

        DISPMANX_UPDATE_HANDLE_T dispman_update;
        dispman_handle = vc_dispmanx_display_open( 0 /* LCD */);
        dispman_update = vc_dispmanx_update_start( 0 );
        dispman_element = vc_dispmanx_element_add ( dispman_update, dispman_handle, 0/*layer*/, &dst_rect, 0/*src*/, &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, DISPMANX_TRANSFORM_T(0)/*transform*/);

        nativewindow.element = dispman_element;
        nativewindow.width = aWidth;
        nativewindow.height = aHeight;
        vc_dispmanx_update_submit_sync( dispman_update );

    }

    EGLNativeDisplayType getDisplay() {
        return EGL_DEFAULT_DISPLAY;
    }

    EGLNativeWindowType getWindow() {
        return reinterpret_cast<EGLNativeWindowType>(&nativewindow);
    }

};

BCM_Host Window_BCM::s_bcm_host;

#endif

native::Window* native::Window::createNew(unsigned width, unsigned height) {

#ifdef USE_X
    return new Window_X(width, height, "");
#elif defined(RASPBERRY_PI)
    return new Window_BCM(width, height);
#endif

}

void native::Window::destroy(Window *w) {
    delete w;
}


