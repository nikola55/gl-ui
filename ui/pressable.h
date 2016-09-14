#ifndef PRESSABLE_H
#define PRESSABLE_H
#include "view.h"
namespace ui {

class Pressable {

public:

    virtual bool pressed() const = 0;
    virtual void pressed(bool) = 0;

    class OnPressHandler {
    public:
        virtual void onPressed(shared_ptr<View>) = 0;
    };

    virtual void onPress(shared_ptr<OnPressHandler>);

    virtual shared_ptr<OnPressHandler> onPress();

};

}
#endif // PRESSABLE_H
