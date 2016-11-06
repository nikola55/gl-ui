#include <unistd.h>
#include <string>
#include "channel_view.h"
#include <root_layout_gl.h>
#include <view_factory_gl.h>
#include <list_layout_gl.h>
#include <label.h>

using ui::shared_ptr;

using gl::ViewFactory_GL;
using gl::RootLayout_GL;
using ui::Icon;
using ui::Label;
using ui::ListLayout;
using ui::AbsoluteLayout;

int main(int argc, char * argv[]) {

    shared_ptr<RootLayout_GL> root = RootLayout_GL::create(800, 600);
    shared_ptr<ViewFactory_GL> viewFactory = new ViewFactory_GL;
    shared_ptr<ChannelView> chView = new ChannelView(L"БНТ 1 HD", L"15:30 - 16:30 Още от деня на изборите", "/home/nikola/Desktop/logo_bnt.png");
    shared_ptr<ChannelView> chView2 = new ChannelView(L"bTV HD", L"15:30 - 16:30 Студио Избори 2016", "/home/nikola/Desktop/logo_btv.png");
    shared_ptr<ListLayout> ll = viewFactory->makeListLayout(false);

    ll->addChild(chView2);
    ll->addChild(chView);
    ll->addChild(chView2);
    ll->addChild(chView);
    ll->addChild(chView2);
    ll->addChild(chView);

    shared_ptr<Icon> icon = viewFactory->makeIcon("/home/nikola/7031585-purple-plain-background.jpg");

    shared_ptr<AbsoluteLayout> absLayout = viewFactory->makeAbsoluteLayout();

    absLayout->addChild(icon);
    absLayout->addChild(ll);

    root->addChild(absLayout);

    while(1) {

        root->draw();

        usleep(1000*30);
    }

}
