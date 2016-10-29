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
