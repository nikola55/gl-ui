#include "list_layout.h"

ui::ListLayout::ListLayout(bool horizontal) :
    m_horizontal(horizontal) {
}

void ui::ListLayout::addChild(shared_ptr<View> chld) {
    m_children.push_back(chld);
    RectangleBaseLayout::changed(true);
}

void ui::ListLayout::removeChild(shared_ptr<View> chld) {
    typedef std::list<shared_ptr<View> >::iterator ViewIter;
    for(ViewIter i = m_children.begin() ; i != m_children.end() ;) {
        const View *v = *i;
        if(v == chld) {
            i = m_children.erase(i);
            RectangleBaseLayout::changed(true);
        } else {
            i++;
        }
    }
}
