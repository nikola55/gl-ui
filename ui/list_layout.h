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
    uint childrenCount() const { return m_Children.size(); }

protected:
    std::list<shared_ptr<View> > m_Children;
    bool horizontal() const {
        return m_Horizontal;
    }

private:
    bool m_Horizontal;
};

}
#endif // LISTLAYOUT_H
