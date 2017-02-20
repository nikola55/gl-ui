#ifndef PRESSABLE_H
#define PRESSABLE_H

namespace ui {

class View;

class Pressable {

    bool m_pressed;

public:

    Pressable() : m_pressed(false) { }

    virtual ~Pressable() { }

    virtual bool pressed() const { return false; }
    virtual void pressed(bool) { }

    class OnPressHandler {
    public:
        virtual void onPressed(View*) = 0;
    };

    virtual void onPressHandler(OnPressHandler*) { }

    virtual OnPressHandler* onPressHandler() { return 0; }

};

}
#endif // PRESSABLE_H
