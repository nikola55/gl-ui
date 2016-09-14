#ifndef TEXTINPUT_H
#define TEXTINPUT_H
#include "rectangle_base_view.h"
#include <string>
namespace ui {

class TextInput : public RectangleBaseView {
public:
    virtual std::string input() const = 0;
    virtual void input(const std::string &) = 0;
};

}
#endif // TEXTINPUT_H
