#ifndef FOCUSABLE_H
#define FOCUSABLE_H

namespace ui {

class View;

class Focusable {
    bool m_focused;
public:
    Focusable() : m_focused(false) { }
    virtual ~Focusable() { }
    virtual bool focused() const { return m_focused; }
    virtual void focused(bool f) { m_focused = f; }

    class OnFocusHandler {
        virtual void onFocused(View*) = 0;
    };

    virtual void onFocusHandler(OnFocusHandler*) { }

    virtual OnFocusHandler* onFocusHandler() { return 0; }

};
}
#endif // FOCUSABLE_H
