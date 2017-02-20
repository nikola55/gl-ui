#ifndef ROOT_LAYOUT_SDL_H
#define ROOT_LAYOUT_SDL_H
#include <SDL2/SDL.h>
#include "rectangle_base_layout.h"

namespace gl {

class RootLayout_SDL : public ui::RectangleBaseLayout {

    RootLayout_SDL(const RootLayout_SDL&);
    RootLayout_SDL& operator=(const RootLayout_SDL&);

    RootLayout_SDL(ui::point pos, ui::uint w, ui::uint h);

public:

    static ui::shared_ptr<RootLayout_SDL> create(ui::point pos, ui::uint w, ui::uint h);

    void addChild(View *chld);

    void draw();

    ~RootLayout_SDL();

private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    ui::mat3 T;
};

}
#endif // ROOT_LAYOUT_SDL_H
