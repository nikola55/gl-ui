#include "rectangle_base_view.h"

ui::RectangleBaseView::RectangleBaseView() :
    m_width(0),
    m_height(0),
    m_margin(0),
    m_padding(0),
    m_changed(true) {
    m_position.x = 0;
    m_position.y = 0;
}
