#include <iostream>
#include <unistd.h>
#include "view_factory_gl.h"
#include "root_layout_gl.h"
#include "icon_gl.h"
#include "absolute_layout_gl.h"
#include "list_layout_gl.h"
#include "glyph_atlas.h"
#include "label_gl.h"
#include "example_custom_view_gl.h"
#include <unistd.h>

using gl::RootLayout_GL;
using gl::ViewFactory_GL;

using ui::ViewFactory;
using ui::shared_ptr;
using ui::point;

int main(int argc, char *argv[]) {

    shared_ptr<RootLayout_GL> root = RootLayout_GL::create(1366, 768);
    shared_ptr<ViewFactory> viewFactory = new ViewFactory_GL;

    shared_ptr<ui::AbsoluteLayout> screen = viewFactory->makeAbsoluteLayout();
    screen->width(root->width());
    screen->height(root->height());

    shared_ptr<ui::Icon> background = viewFactory->makeIcon("/home/nikola/7031585-purple-plain-background.jpg");
    background->width(root->width());
    background->height(root->height());
    screen->addChild(background);

    shared_ptr<gl::ExampleCustomView_GL> ex =
            new gl::ExampleCustomView_GL("/home/nikola/Downloads/tv_15.png",
                                         "Watch TV", 18, gl::ExampleCustomView_GL::RIGHT);

    point pos = { 100, 100 };
    ex->position(pos);
    ex->height(50);
    ex->width(50);
    screen->addChild(ex);

    root->addChild(screen);

    while(true) {
        root->draw();
        usleep(33333);
        pause();
    }

}
