#ifndef VIEW_H
#define VIEW_H
#include "ui_common.h"
#include "focusable.h"
#include "pressable.h"

namespace ui {

class View : public Focusable, public Pressable {

public:

    View();

    virtual point position() const = 0;
    virtual void position(point) = 0;

    virtual uint width() const = 0;
    virtual void width(uint) = 0;

    virtual uint height() const = 0;
    virtual void height(uint) = 0;

    virtual uint margin() const = 0;
    virtual void margin(uint) = 0;

    virtual uint padding() const = 0;
    virtual void padding(uint) = 0;

    virtual bool changed() const = 0;
    virtual void changed(bool) = 0;

    virtual void draw() = 0;

    virtual void setParent(View* p);

    virtual View* getParent();

    virtual ~View();

private:

    View* m_parent;

};

}

#endif // VIEW_H
