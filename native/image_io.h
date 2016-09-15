#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include "ui_common.h"
#include <string>
#include <GLES2/gl2.h>

namespace native {

GLuint loadFromURI(const std::string& URI, GLuint& w_out, GLuint& h_out);

ui::image loadFromFile(const std::string &path);

}

#endif // IMAGE_IO_H
