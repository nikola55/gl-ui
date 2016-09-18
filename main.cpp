#include <iostream>
#include <unistd.h>
#include "root_layout_gl.h"
#include "icon_gl.h"
#include "absolute_layout_gl.h"
#include "list_layout_gl.h"
#include "glyph_atlas.h"
#include "label_gl.h"
#include <unistd.h>

using gl::RootLayout_GL;

int main(int argc, char *argv[])
{
    ui::shared_ptr<RootLayout_GL> root = RootLayout_GL::create(800, 600);
    ui::shared_ptr<ui::Layout> screen = new gl::AbsoluteLayout_GL;

//    screen->width(root->width());
//    screen->height(root->height());

    ui::shared_ptr<ui::View> background = new gl::Icon_GL("/home/nikola/7031585-purple-plain-background.jpg");
    background->width(root->width());
    background->height(root->height());
    screen->addChild(background);


    ui::shared_ptr<gl::Label_GL> label = new  gl::Label_GL("decoder technical itch", 24);
    ui::point p = { 100, 100 };
    label->position(p);

    ui::shared_ptr<ui::View> listViewBox = new gl::Icon_GL("/home/nikola/label_box.png");
    listViewBox->width(label->width()+20);
    listViewBox->height(label->height()+20);
    listViewBox->margin(10);
    ui::point p2 = { p.x - 10, p.y - 10 };
    listViewBox->position(p2);

    screen->addChild(listViewBox);
    screen->addChild(label);
    root->addChild(screen);
    while(true) {
        root->draw();
        usleep(33333);
        pause();
    }

}
