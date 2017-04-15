#ifndef VIEWFACTORY_GL_H
#define VIEWFACTORY_GL_H

#include "view_factory.h"

namespace gl {

class ViewFactory_GL : public ui::ViewFactory {
public:

    ui::shared_ptr<ui::Label> makeLabel(const std::wstring &text, ui::uint sz);

    ui::shared_ptr<ui::Icon> makeIcon(const std::string &URI);

    ui::shared_ptr<ui::ListLayout> makeListLayout(bool horiz);

    ui::shared_ptr<ui::AbsoluteLayout> makeAbsoluteLayout();

    ui::shared_ptr<ui::Layout> makeRootLayout(uint sx, uint sy, uint w, uint h);

};

}
#endif // VIEWFACTORY_GL_H
