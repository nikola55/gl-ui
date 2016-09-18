#ifndef VIEWFACTORY_GL_H
#define VIEWFACTORY_GL_H
#include "view_factory.h"

namespace gl {

class ViewFactory_GL : public ui::ViewFactory {
public:

    ui::shared_ptr<ui::Label> makeLabel(const std::string &text, ui::uint sz);

    ui::shared_ptr<ui::Icon> makeIcon(const std::string &URI);

    ui::shared_ptr<ui::ListLayout> makeListLayout(bool horiz);

    ui::shared_ptr<ui::AbsoluteLayout> makeAbsoluteLayout();

};

}
#endif // VIEWFACTORY_GL_H
