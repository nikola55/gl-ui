#include <iostream>
#include <unistd.h>
#include "root_layout_gl.h"
#include "icon_gl.h"
#include "absolute_layout_gl.h"
#include "list_layout_gl.h"
#include <unistd.h>

using gl::RootLayout_GL;

int main(int argc, char *argv[])
{
    ui::shared_ptr<RootLayout_GL> root = RootLayout_GL::create(800, 600);
    ui::shared_ptr<ui::Layout> screen = new gl::AbsoluteLayout_GL;

    screen->width(root->width());
    screen->height(root->height());

    ui::shared_ptr<ui::View> background = new gl::Icon_GL("/home/nikola/7031585-purple-plain-background.jpg");
    background->width(root->width());
    background->height(root->height());
    screen->addChild(background);
    ui::shared_ptr<ui::View> listViewBox = new gl::Icon_GL("/home/nikola/shadow.png");
    ui::point textBoxPos = { 100, 100 };
    listViewBox->width(600);
    listViewBox->height(300);
    listViewBox->position(textBoxPos);


    ui::shared_ptr<ui::Layout> list = new gl::ListLayout_GL(false);
    list->height(300);
    list->width(600);
    list->padding(10);
    ui::point pos = { 100, 100 };
    list->position(pos);

    ui::shared_ptr<ui::View> icon = new gl::Icon_GL("/home/nikola/BNT1_logo.svg.png");
    icon->width(150);
    icon->height(150);
    list->addChild(icon);
    list->addChild(icon);
    list->addChild(icon);
    list->addChild(icon);
    list->addChild(icon);
    list->addChild(icon);

    screen->addChild(list);
    screen->addChild(listViewBox);

    root->addChild(screen);
    while(true) {
        root->draw();
        usleep(33333);
        pause();
    }

}
