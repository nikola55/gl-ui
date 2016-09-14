#include "list_layout.h"

ui::ListLayout::ListLayout(bool horizontal) :
    m_Horizontal(horizontal) {
}

void ui::ListLayout::addChild(shared_ptr<View> chld) {
    m_Children.push_back(chld);
}

void ui::ListLayout::removeChild(shared_ptr<View> chld) {
    typedef std::list<shared_ptr<View> >::iterator ViewIter;
    for(ViewIter i = m_Children.begin() ; i != m_Children.end() ; i++) {
        const View *v = *i;
        if(v == chld) {
            i = m_Children.erase(i);
        }
    }
}
