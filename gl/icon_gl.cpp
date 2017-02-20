#include "icon_gl.h"
#include <assert.h>

using ui::Icon;
using ui::mat3;
using ui::eye3x3;

using gl::Icon_GL;
using gl::Texture;
using gl::Drawable_GL;
using gl::VertexBuffer;
using gl::ShaderProgram;

Icon_GL::Icon_GL(const std::string &URI) :
    Icon(URI),
    m_texture(new Texture(URI)),
    m_coord(VertexBuffer<GLfloat>::getRect3(m_texture->width(), m_texture->height())),
    m_texCoord(VertexBuffer<GLfloat>::getSquareTexCoord()),
    m_shader(new ShaderProgram(sc_vertexShader, sc_fragShader)) {

    ui::eye3x3(m_transf);

    width(m_texture->width());
    height(m_texture->height());

}

Icon_GL::Icon_GL(ui::shared_ptr<Texture> texture) :
    Icon("<anonymous>"),
    m_texture(texture),
    m_coord(VertexBuffer<GLfloat>::getRect3(m_texture->width(), m_texture->height())),
    m_texCoord(VertexBuffer<GLfloat>::getSquareTexCoord()),
    m_shader(new ShaderProgram(sc_vertexShader, sc_fragShader)) {

    ui::eye3x3(m_transf);

    width(m_texture->width());
    height(m_texture->height());
}

void Icon_GL::draw() {
    assert(m_shader->compiled());
    m_shader->enable();
    assert(glGetError() == GL_NO_ERROR);

    assert(m_texCoord->created());
    glBindBuffer(GL_ARRAY_BUFFER, m_texCoord->getId());
    GLint coordLocation = m_shader->attributeLocation("a_coord");
    glVertexAttribPointer(coordLocation, 2, GL_FLOAT, 0, 8, 0);
    glEnableVertexAttribArray(coordLocation);
    assert(glGetError()==GL_NO_ERROR);

    assert(m_coord->created());
    glBindBuffer(GL_ARRAY_BUFFER, m_coord->getId());
    GLint positionLocation = m_shader->attributeLocation("a_pos");
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, 0, 12, 0);
    glEnableVertexAttribArray(positionLocation);
    assert(glGetError()==GL_NO_ERROR);

    // do scaling
    static mat3 S;
    eye3x3(S);
    S(0,0) = float(width()) / float(m_texture->width());
    S(1,1) = float(height()) / float(m_texture->height());
    m_transf = m_transf*S;

    GLint transformLocation = m_shader->uniformLocation("u_T");
    glUniformMatrix3fv(transformLocation, 1, GL_FALSE, &m_transf(0,0));
    assert(glGetError()==GL_NO_ERROR);

    assert(m_texture->loaded());
    GLint textureLocation = m_shader->uniformLocation("u_icon");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->getTextureId());
    glUniform1i(textureLocation, 0);
    assert(glGetError()==GL_NO_ERROR);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    assert(glGetError()==GL_NO_ERROR);

    changed(false);
}

const std::string Icon_GL::sc_vertexShader =
    "precision mediump float;\n"
    "attribute vec3 a_pos;\n"
    "attribute vec2 a_coord;\n"
    "varying vec2 v_coord;\n"
    "uniform mat3 u_T;\n"
    "void main() {\n"
    "   gl_Position = vec4(u_T*a_pos, 1.0);\n"
    "   v_coord = a_coord;\n"
    "}\n";

const std::string Icon_GL::sc_fragShader =
    "precision mediump float;\n"
    "varying vec2 v_coord;\n"
    "uniform sampler2D u_icon;\n"
    "void main() {\n"
    "   gl_FragColor = texture2D(u_icon, v_coord);\n"
    "}\n";
