#ifndef LABEL_H
#define LABEL_H
#include "rectangle_base_view.h"
#include <string>

namespace ui {

class Label : public RectangleBaseView {
public:

    virtual const std::string& text() const = 0;
    virtual void text(const std::string& text)  = 0;

    virtual void size(uint) = 0;
    virtual uint size() const = 0;

private:

};

}
#endif // LABEL_H
