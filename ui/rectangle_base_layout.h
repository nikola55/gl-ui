#ifndef RECTANGLEBASELAYOUT_H
#define RECTANGLEBASELAYOUT_H
#include "layout.h"
namespace ui {
class RectangleBaseLayout : public Layout {
public:
    RectangleBaseLayout() :
        m_width(0),
        m_height(0),
        m_padding(0),
        m_margin(0),
        m_changed(true) {
        m_position.x = 0;
        m_position.y = 0;
    }

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

    uint height() const {  return m_height; }

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
    void changed(bool c) { m_changed = c; }

private:

    point m_position;
    uint m_width;
    uint m_height;
    uint m_padding;
    uint m_margin;
    bool m_changed;
};
}
#endif // RECTANGLEBASELAYOUT_H
