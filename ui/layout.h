#ifndef LAYOUT_H
#define LAYOUT_H
#include "view.h"
namespace ui {

class Layout : public View {
public:
    virtual void addChild(shared_ptr<View> chld) = 0;
    virtual shared_ptr<View> getChild(uint idx) const = 0;
    virtual void removeChild(shared_ptr<View> chld) = 0;
    virtual uint childrenCount() const = 0;
protected:
    virtual void beforeDraw(const shared_ptr<View>& chld) = 0;
};

}
#endif // LAYOUT_H
