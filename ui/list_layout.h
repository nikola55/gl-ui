#ifndef LISTLAYOUT_H
#define LISTLAYOUT_H
#include "rectangle_base_layout.h"
#include <list>

namespace ui {

class ListLayout : public RectangleBaseLayout {
public:

    ListLayout(bool horizontal);

protected:

    bool horizontal() const {
        return m_horizontal;
    }

private:
    bool m_horizontal;
};

}
#endif // LISTLAYOUT_H
