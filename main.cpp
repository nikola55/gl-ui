#include <iostream>
#include <unistd.h>
#include "view_factory_gl.h"
#include "root_layout_gl.h"
#include "icon_gl.h"
#include "absolute_layout_gl.h"
#include "list_layout_gl.h"
#include "glyph_atlas.h"
#include "label_gl.h"
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

    shared_ptr<ui::Label> label =viewFactory->makeLabel("Yes", 24);
    point p = { 100, 100 };
    label->position(p);

    shared_ptr<ui::Icon> labelBox = viewFactory->makeIcon("/home/nikola/label_box.png");
    labelBox->width(label->width()+20);
    labelBox->height(label->height()+20);
    labelBox->margin(10);
    point p2 = { p.x - 10, p.y - 10 };
    labelBox->position(p2);

    screen->addChild(labelBox);
    screen->addChild(label);
    root->addChild(screen);

    while(true) {
        root->draw();
        usleep(33333);
    }

}
