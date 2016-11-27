#ifndef LISTLAYOUT_H
#define LISTLAYOUT_H
#include "rectangle_base_layout.h"
#include <list>

namespace ui {

class ListLayout : public RectangleBaseLayout {
public:
    ListLayout(bool horizontal);

    void addChild(shared_ptr<View> chld);
    void removeChild(shared_ptr<View> chld);
    uint childrenCount() const { return m_children.size(); }

    bool changed() const {
        std::list< shared_ptr<View> >::const_iterator chld = m_children.begin();
        bool changed = false;
        for(; chld != m_children.end() ; chld++) {
            const shared_ptr<View>& v = *chld;
            if(v && v->changed()) {
                changed=true;
                break;
            }

        }
        return changed || RectangleBaseLayout::changed();
    }

protected:

    std::list< shared_ptr<View> > m_children;

    bool horizontal() const {
        return m_horizontal;
    }

private:
    bool m_horizontal;
};

}
#endif // LISTLAYOUT_H
