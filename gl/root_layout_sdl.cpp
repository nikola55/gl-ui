#include "root_layout_sdl.h"
#include "drawable_gl.h"

#include <GLES2/gl2.h>

#include <cassert>

using ui::uint;
using ui::point;
using ui::mat3;
using ui::View;

using gl::RootLayout_SDL;

static const class InitializeSDL {
public:
    InitializeSDL() {
        m_initialized = SDL_Init(SDL_INIT_EVERYTHING) >= 0;
    }
    ~InitializeSDL() {
        SDL_Quit();
    }
    bool ok() const {
        return m_initialized;
    }
private:
    bool m_initialized;
} sc_sdl_init;

static void setGLAttribute(SDL_GLattr attr, int value) {
    bool res = SDL_GL_SetAttribute(attr, value) != 0;
    assert(res);
}

RootLayout_SDL::RootLayout_SDL(point pos, uint w, uint h) :
    m_window(0) {

    position(pos);
    width(w);
    height(h);

    bool res = sc_sdl_init.ok();
    assert(res);
    SDL_DisplayMode videomode;
    res = SDL_GetCurrentDisplayMode (0, &videomode) != 0;
    assert(res);

    setGLAttribute(SDL_GL_RED_SIZE, 8);
    setGLAttribute(SDL_GL_GREEN_SIZE, 8);
    setGLAttribute(SDL_GL_BLUE_SIZE, 8);
    setGLAttribute(SDL_GL_DEPTH_SIZE, 16);
    setGLAttribute(SDL_GL_DOUBLEBUFFER, 1);

    setGLAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    setGLAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    setGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    m_window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL);
    assert(m_window!=0);

    m_glContext = SDL_GL_CreateContext(m_window);
    assert(m_glContext!=0);

    T(0,0) = 2.0/w; T(0, 1) = 0.0; T(0, 2) = -1.0;
    T(1,0) = 0.0; T(1, 1) = 2.0/h; T(1, 2) = -1.0;
    T(2,0) = 0.0; T(2, 1) = 0.0; T(2,2) = 1.0;

    glEnable(GL_SCISSOR_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Drawable_GL::initAuxiliaryFrameBuffer();

}

ui::shared_ptr<gl::RootLayout_SDL> RootLayout_SDL::create(ui::point pos, ui::uint w, ui::uint h) {
    return new RootLayout_SDL(pos, w, h);
}

RootLayout_SDL::~RootLayout_SDL() {
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
}

void RootLayout_SDL::addChild(View *chld) {
    if(childrenCount()==0) {
        RectangleBaseLayout::addChild(chld);
    }
}

void RootLayout_SDL::draw() {

    static mat3 transl, transf;

    if(!changed()) {
        return;
    }
    if(childrenCount() == 0) {
        return;
    }
    View* rootView = getChild(0);
    point pos = rootView->position();
    if(Drawable_GL *drawable = dynamic_cast<Drawable_GL*>(rootView)) {
        eye3x3(transl);
        transl(0,2) = pos.x;
        transl(1,2) = pos.y;
        transf = T*transl;
        drawable->transform(transf);
        glViewport(0, 0, width(), height());
        rootView->draw();
        SDL_GL_SwapWindow(m_window);
    }
}
