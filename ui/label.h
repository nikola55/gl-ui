#ifndef LABEL_H
#define LABEL_H
#include "rectangle_base_view.h"
#include <string>

namespace ui {

class Label : public RectangleBaseView {
public:

    virtual const std::wstring& text() const = 0;
    virtual void text(const std::wstring& text) = 0;

    virtual void size(uint) = 0;
    virtual uint size() const = 0;

    virtual void text_color(byte,byte,byte) = 0;

private:

};

}
#endif // LABEL_H
