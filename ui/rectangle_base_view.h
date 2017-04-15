#ifndef RECTANGLEBASEVIEW_H
#define RECTANGLEBASEVIEW_H
#include "view.h"

namespace ui {
class RectangleBaseView : public View {
public:

    RectangleBaseView();

    point position() const { return m_position; }

    void position(point p) {
        m_position = p;
        changed(true);
    }

    uint width() const { return m_width; }

    void width(uint w) {
        m_width = w;
        changed(true);
    }

    uint height() const { return m_height; }

    void height(uint h) {
        m_height = h;
        changed(true);
    }

    uint margin() const { return m_margin; }

    void margin(uint m) {
        m_margin = m;
        changed(true);
    }

    uint padding() const { return m_padding; }

    void padding(uint p) {
        m_padding = p;
        changed(true);
    }

    bool changed() const { return m_changed; }

    void changed(bool c) {
        if(View*p = getParent()) {
            p->changed(c);
        }
        m_changed = true;
    }

protected:
    point m_position;
    uint m_width;
    uint m_height;
    uint m_margin;
    uint m_padding;
    bool m_changed;
};
}
#endif // RECTANGLEBASEVIEW_H
