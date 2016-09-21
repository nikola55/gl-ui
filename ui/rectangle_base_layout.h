#ifndef RECTANGLEBASELAYOUT_H
#define RECTANGLEBASELAYOUT_H
#include "layout.h"
namespace ui {
class RectangleBaseLayout : public Layout {

public:

    RectangleBaseLayout() :
        m_Width(0),
        m_Height(0),
        m_Padding(0),
        m_Margin(0) {

        m_Position.x = 0;
        m_Position.y = 0;
        m_Background.red = 0;
        m_Background.green = 0;
        m_Background.blue = 0;
        m_Background.alpha = 0;

    }

    point position() const { return m_Position; }
    void position(point p) { m_Position = p; }

    uint width() const { return m_Width; }
    void width(uint w) { m_Width = w; }

    uint height() const {  return m_Height; }
    void height(uint h) { m_Height = h; }

    uint margin() const { return m_Margin; }
    void margin(uint m) { m_Margin = m; }

    uint padding() const { return m_Padding; }
    void padding(uint p) { m_Padding = p; }

    color background() const { return m_Background; }
    void background(color c) { m_Background = c; }

private:
    color m_Background;
    point m_Position;
    uint m_Width;
    uint m_Height;
    uint m_Padding;
    uint m_Margin;
};
}
#endif // RECTANGLEBASELAYOUT_H
