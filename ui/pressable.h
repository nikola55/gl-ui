#ifndef PRESSABLE_H
#define PRESSABLE_H
#include "ui_common.h"

namespace ui {

class View;

class Pressable {

    bool m_pressed;

public:

    Pressable() : m_pressed(false) { };

    virtual ~Pressable() { };

    virtual bool pressed() const { return false; };
    virtual void pressed(bool) { };

    class OnPressHandler {
    public:
        virtual void onPressed(shared_ptr<View>) = 0;
    };

    virtual void onPressHandler(shared_ptr<OnPressHandler>) { };

    virtual shared_ptr<OnPressHandler> onPressHandler() { return 0; };

};

}
#endif // PRESSABLE_H
