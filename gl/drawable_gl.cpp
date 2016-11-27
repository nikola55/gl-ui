#include "drawable_gl.h"
#include <GLES2/gl2.h>

using gl::Drawable_GL;

static GLuint s_auxiliary_fb = 0;

void Drawable_GL::initAuxiliaryFrameBuffer() {
    glGenFramebuffers(1, &s_auxiliary_fb);
}

void Drawable_GL::destroyAuxiliaryFrameFuffer() {
    glDeleteFramebuffers(1, &s_auxiliary_fb);
}

void Drawable_GL::useAuxiliaryFrameBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, s_auxiliary_fb);
}

void Drawable_GL::unuseAuxiliaryFrameBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
