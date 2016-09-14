#ifndef LABEL_H
#define LABEL_H
#include "rectangle_base_view.h"
#include <string>

namespace ui {

class Label : public RectangleBaseView {
public:
    Label(const std::string& text="");

    const std::string& text() const { return m_Text; }
    void text(const std::string& text) { m_Text = text; }

private:
    std::string m_Text;
};

}
#endif // LABEL_H
