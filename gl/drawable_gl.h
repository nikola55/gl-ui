#ifndef DRAWABLE_GL_H
#define DRAWABLE_GL_H
#include "ui_common.h"
namespace gl {

class Drawable_GL {

public:

    virtual void transform(ui::mat) = 0;

    virtual ui::mat transform() = 0;
};

}
#endif // DRAWABLE_GL_H
