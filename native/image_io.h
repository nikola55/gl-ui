#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include "ui_common.h"
#include <string>
#include <GLES2/gl2.h>

namespace native {

ui::image loadFromFile(const std::string &path);

}

#endif // IMAGE_IO_H
