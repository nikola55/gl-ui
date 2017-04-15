#include "rectangle_base_layout.h"


ui::RectangleBaseLayout::RectangleBaseLayout() :
    m_width(0),
    m_height(0),
    m_padding(0),
    m_margin(0),
    m_changed(true) {
    m_position.x = 0;
    m_position.y = 0;
}

void ui::RectangleBaseLayout::removeChild(ui::View *chld) {
    void* base = dynamic_cast<void*>(chld);
    std::vector<View*>::iterator chldItr = m_children.begin();
    while(chldItr!=m_children.end()) {
        View *x = *chldItr;
        if(base == dynamic_cast<void*>(x)) {
            chldItr = m_children.erase(chldItr);
            (*chldItr)->setParent(0);
            changed(true);
        } else {
            chldItr++;
        }
    }
}

bool ui::RectangleBaseLayout::changed() const {
    return m_changed;
}
