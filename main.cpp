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
    ui::point listViewPos = { 50, 50 };
    listViewBox->width(700);
    listViewBox->height(120);
    listViewBox->margin(15);
    listViewBox->position(listViewPos);


    ui::shared_ptr<ui::Layout> list = new gl::ListLayout_GL(true);
    list->height(120);
    list->width(700);
    list->padding(10);
    ui::point pos = { 50, 50 };
    list->position(pos);

    ui::shared_ptr<ui::View> icon = new gl::Icon_GL("/home/nikola/387b93c8b66379c32e1cc2b98dcf5197.png");
    icon->width(120);
    icon->height(120);
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
