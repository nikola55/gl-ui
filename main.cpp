#include <unistd.h>

#include <root_layout_gl.h>
#include <view_factory_gl.h>
#include <icon.h>

using ui::shared_ptr;

using gl::ViewFactory_GL;
using gl::RootLayout_GL;
using ui::Icon;

int main(int argc, char * argv[]) {

    shared_ptr<RootLayout_GL> root = RootLayout_GL::create(1366, 768);
    shared_ptr<ViewFactory_GL> viewFactory = new ViewFactory_GL;
    shared_ptr<Icon> icon = viewFactory->makeIcon("/home/nikola/7031585-purple-plain-background.jpg");
    root->addChild(icon);

    while(1) {

        root->draw();

        usleep(1000*40);
    }

}
