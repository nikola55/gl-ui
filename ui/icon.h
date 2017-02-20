#ifndef ICON_H
#define ICON_H
#include "rectangle_base_view.h"
#include <string>
namespace ui {
class Icon : public RectangleBaseView {
public:
    Icon(const std::string &URI) :
        m_URI(URI) {
    }
private:
    std::string m_URI;
};
}

#endif // ICON_H
