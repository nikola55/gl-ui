#ifndef FOCUSABLE_H
#define FOCUSABLE_H
namespace ui {
class Focusable {
    bool m_focused;
public:
    Focusable() : m_focused(false) { };
    virtual ~Focusable() { };
    virtual bool focused() const { return m_focused; };
    virtual void focused(bool f) { m_focused = f; };
};
}
#endif // FOCUSABLE_H
