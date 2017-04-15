#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H

#include "ui_common.h"

namespace ui {

class Label;
class Icon;
class Layout;
class ListLayout;
class AbsoluteLayout;

class ViewFactory {
public:
    virtual shared_ptr<Label> makeLabel(const std::wstring &text, uint sz) = 0;
    virtual shared_ptr<Icon> makeIcon(const std::string &URI) = 0;
    virtual shared_ptr<ListLayout> makeListLayout(bool) = 0;
    virtual shared_ptr<AbsoluteLayout> makeAbsoluteLayout() = 0;
    virtual shared_ptr<Layout> makeRootLayout(uint sx, uint sy, uint w, uint h) = 0;
public:
    virtual ~ViewFactory();
};

}

#endif // VIEWFACTORY_H
