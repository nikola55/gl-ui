#ifndef DRAWABLE_GL_H
#define DRAWABLE_GL_H
#include "ui_common.h"
namespace gl {

class Drawable_GL {

public:

    virtual void transform(const ui::mat3&) = 0;

    virtual const ui::mat3& transform() const = 0;
};

}
#endif // DRAWABLE_GL_H
