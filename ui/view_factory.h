#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H
#include "ui_common.h"
#include "label.h"
#include "icon.h"
#include "text_input.h"
#include "list_layout.h"
namespace ui {

class ViewFactory {
public:
    virtual shared_ptr<Label> makeLabel(const std::string &text="") = 0;
    virtual shared_ptr<Icon> makeIcon(const std::string &URI="") = 0;
    virtual shared_ptr<TextInput> makeTextInput() = 0;
    virtual shared_ptr<ListLayout> makeListLayout(bool) = 0;
};

}

#endif // VIEWFACTORY_H
