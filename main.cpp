#include <unistd.h>

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

    listLayout->addChild(viewFactory->makeLabel("Hello", 15));
    listLayout->addChild(viewFactory->makeLabel("World", 15));

    ui::point p = { 100, 100 };

    listLayout->position(p);

    shared_ptr<Icon> icon = viewFactory->makeIcon("/home/nikola/7031585-purple-plain-background.jpg");

    shared_ptr<AbsoluteLayout> absLayout = viewFactory->makeAbsoluteLayout();

    absLayout->addChild(icon);
    absLayout->addChild(listLayout);

    root->addChild(absLayout);

    while(1) {

        root->draw();

        usleep(1000*40);
    }

}
