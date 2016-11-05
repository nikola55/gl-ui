#include <unistd.h>
#include <string>

#include <root_layout_gl.h>
#include <view_factory_gl.h>
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

    shared_ptr<ListLayout> listLayout = viewFactory->makeListLayout(false);

    wchar_t e = 1045;
    wchar_t f = 1060;
    wchar_t i = 1048;
    wchar_t r = 1056;
    wchar_t n = 1053;

    std::wstring str;
    str+=e; str+=f; str+=i; str+=r; str+=n; str+=i;
    shared_ptr<Label> lab = viewFactory->makeLabel(str, 35);
    lab->text_color(64, 128, 192);

    listLayout->addChild(lab);
    listLayout->addChild(viewFactory->makeLabel(L"World", 20));

    ui::point p = { 100, 100 };

    listLayout->position(p);

    shared_ptr<Icon> icon = viewFactory->makeIcon("/home/nikola/7031585-purple-plain-background.jpg");

    shared_ptr<AbsoluteLayout> absLayout = viewFactory->makeAbsoluteLayout();

    absLayout->addChild(icon);
    absLayout->addChild(listLayout);

    root->addChild(absLayout);

    float vx = 5.0;
    float vy = 5.0;

    while(1) {

        root->draw();
        if(p.x == 0 || p.x==800) {
            vx*=-1;
            lab->size(35);
        }
        if(p.y == 0 || p.y==600) {
            vy*=-1;
            lab->size(25);
        }
        p.x += vx;
        p.y += vy;

        listLayout->position(p);

        usleep(1000*33);
    }

}
