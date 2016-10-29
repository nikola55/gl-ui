#ifndef ABSOLUTELAYOUT_H
#define ABSOLUTELAYOUT_H

#include "rectangle_base_layout.h"
#include <list>

namespace ui {

class AbsoluteLayout : public RectangleBaseLayout {
public:
    void addChild(shared_ptr<View> chld);
    void removeChild(shared_ptr<View> chld);
    uint childrenCount() const { return m_children.size(); }
protected:
    std::list< shared_ptr<View> > m_children;
};

}

#endif // ABSOLUTELAYOUT_H
