#ifndef FOCUSABLE_H
#define FOCUSABLE_H
namespace ui {
class Focusable {
public:
    virtual bool focused() const = 0;
    virtual void focused(bool) = 0;
};
}
#endif // FOCUSABLE_H
