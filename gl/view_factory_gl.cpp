#include "view_factory_gl.h"
#include "label_gl.h"
#include "icon_gl.h"
#include "list_layout_gl.h"
#include "absolute_layout_gl.h"
#include "root_layout_sdl.h"

using std::string;
using std::wstring;

using ui::ViewFactory;
using ui::Label;
using ui::Icon;
using ui::ListLayout;
using ui::AbsoluteLayout;

using ui::shared_ptr;
using ui::uint;

using gl::ViewFactory_GL;
using gl::Label_GL;
using gl::Icon_GL;
using gl::ListLayout_GL;
using gl::AbsoluteLayout_GL;
using gl::RootLayout_SDL;

shared_ptr<Label> ViewFactory_GL::makeLabel(const wstring &text, uint sz) {
    return new Label_GL(text, sz);
}

shared_ptr<Icon> ViewFactory_GL::makeIcon(const string &URI) {
    return new Icon_GL(URI);
}

shared_ptr<ListLayout> ViewFactory_GL::makeListLayout(bool horiz) {
    return new ListLayout_GL(horiz);
}

shared_ptr<AbsoluteLayout> ViewFactory_GL::makeAbsoluteLayout() {
    return new AbsoluteLayout_GL;
}

ui::shared_ptr<ui::Layout> ViewFactory_GL::makeRootLayout(uint sx, uint sy, uint w, uint h) {
    ui::point pos = { sx, sy };
    return RootLayout_SDL::create(pos, w, h);
}
