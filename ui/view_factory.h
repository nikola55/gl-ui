#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H

#include "ui_common.h"
#include "label.h"
#include "icon.h"
#include "text_input.h"
#include "list_layout.h"
#include "absolute_layout.h"

namespace ui {

class ViewFactory {
public:
    virtual shared_ptr<Label> makeLabel(const std::wstring &text, uint sz) = 0;
    virtual shared_ptr<Icon> makeIcon(const std::string &URI) = 0;
    virtual shared_ptr<ListLayout> makeListLayout(bool) = 0;
    virtual shared_ptr<AbsoluteLayout> makeAbsoluteLayout() = 0;

};

}

#endif // VIEWFACTORY_H
