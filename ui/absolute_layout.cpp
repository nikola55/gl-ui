#include "absolute_layout.h"

using ui::View;
using ui::AbsoluteLayout;
using ui::shared_ptr;

void AbsoluteLayout::addChild(shared_ptr<View> chld) {
    m_children.push_back(chld);
}

void AbsoluteLayout::removeChild(shared_ptr<View> chld) {
    std::list<shared_ptr<View> >::iterator chldIter = m_children.begin();
    for( ; chldIter != m_children.end() ; chldIter++) {
        View *curr = *chldIter;
        if(curr == chld) {
            chldIter = m_children.erase(chldIter);
        }
    }
}
