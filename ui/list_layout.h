#ifndef LISTLAYOUT_H
#define LISTLAYOUT_H
#include "rectangle_base_layout.h"
#include <list>

namespace ui {

class ListLayout : public RectangleBaseLayout {
public:

    ListLayout(bool horizontal);

    uint width() const {
        if(horizontal()) {
            return width_horizontal();
        } else {
            return width_vertical();
        }
    }

    uint height() const {
        if(horizontal()) {
            return height_horizontal();
        } else {
            return height_vertical();
        }
    }

protected:

    uint width_horizontal() const;

    uint width_vertical() const;

    uint height_horizontal() const;

    uint height_vertical() const;

    bool horizontal() const {
        return m_horizontal;
    }

private:
    bool m_horizontal;
};

}
#endif // LISTLAYOUT_H
