#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <EGL/egl.h>

namespace native {

class Window {

    Window(const Window &) { } // = delete

    Window& operator=(const Window &) { } // = delete

protected:

    Window() { }

public:

    virtual EGLNativeDisplayType getDisplay() = 0;

    virtual EGLNativeWindowType getWindow() = 0;

    static Window* createNew(unsigned width, unsigned height);

    static void destroy(Window *);

    virtual ~Window() { }

};

}

#endif // WINDOW_H
