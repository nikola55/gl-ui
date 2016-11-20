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

#define BG_LOC "/home/nikola/7031585-purple-plain-background.jpg"
#define LOGO1_LOC "/home/nikola/Desktop/logo_bnt.png"
#define LOGO2_LOC "/home/nikola/Desktop/logo_btv.png"

int main(int argc, char * argv[]) {

    shared_ptr<RootLayout_GL> root = RootLayout_GL::create(1366, 768);
    shared_ptr<ViewFactory_GL> viewFactory = new ViewFactory_GL;
    shared_ptr<ChannelView> chView = new ChannelView(L"БНТ 1 HD", L"15:30 - 16:30 Още от деня на изборите", LOGO1_LOC);
    shared_ptr<ChannelView> chView2 = new ChannelView(L"bTV HD", L"15:30 - 16:30 Студио Избори 2016", LOGO2_LOC);
    shared_ptr<ListLayout> ll = viewFactory->makeListLayout(false);

    ll->addChild(chView2);
    ll->addChild(chView);
    ll->addChild(chView2);
    ll->addChild(chView);
    ll->addChild(chView2);
    ll->addChild(chView);
    ll->padding(10);

    shared_ptr<Icon> icon = viewFactory->makeIcon(BG_LOC);

    shared_ptr<AbsoluteLayout> absLayout = viewFactory->makeAbsoluteLayout();

    absLayout->addChild(icon);
    absLayout->addChild(ll);
    absLayout->addChild(ll);

    root->addChild(absLayout);

    uint vx=3, vy=3;
    ui::point pos = { 0, 0 };

    while(1) {
//        pos.x+=vx;
//        pos.y+=vy;
//        if(pos.x+chView->width() >= 1366 || pos.x <= 0 ) {
//            vx*=-1;
//        }
//        if(pos.y+chView->height() >= 768 || pos.y <= 0 ) {
//            vy*=-1;
//        }
//        ll->position(pos);
        root->draw();
        usleep(1000*30);
    }

}
