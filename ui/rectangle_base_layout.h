#ifndef RECTANGLEBASELAYOUT_H
#define RECTANGLEBASELAYOUT_H
#include "layout.h"
#include <vector>

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

    void addChild(View* chld) {
        if(chld) {
            chld->setParent(this);
            m_children.push_back(chld); // TODO: check for self
            changed(true);
        }
    }

    View* getChild(uint idx) const {
        if(idx < m_children.size()) {
            return m_children[idx];
        } else {
            return 0;
        }
    }

    void removeChild(View* chld);

    uint childrenCount() const { return m_children.size(); }

    bool changed() const;

    void changed(bool c) {
        if(View*p = getParent()) {
            p->changed(true);
        }
        m_changed = c;
    }

protected:

    void beforeDraw(View* chld) {  }

private:
    std::vector<View*> m_children;
    point m_position;
    uint m_width;
    uint m_height;
    uint m_padding;
    uint m_margin;
    bool m_changed;
};
}
#endif // RECTANGLEBASELAYOUT_H
