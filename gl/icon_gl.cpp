#include "icon_gl.h"
#include <assert.h>

using ui::Icon;
using ui::mat;
using ui::eye3x3;

using gl::Icon_GL;
using gl::Texture;
using gl::Drawable_GL;
using gl::VertexBuffer;
using gl::ShaderProgram;

Icon_GL::Icon_GL(const std::string &URI) :
    Icon(URI),
    T(3,3),
    m_Texture(new Texture(URI)),
    m_Coord(VertexBuffer<GLfloat>::getRect3(m_Texture->width(), m_Texture->height())),
    m_TexCoord(VertexBuffer<GLfloat>::getSquareTexCoord()),
    m_Shader(new ShaderProgram(sc_vertexShader, sc_fragShader)) {

    ui::eye3x3(T);

    width(m_Texture->width());
    height(m_Texture->height());

}

Icon_GL::~Icon_GL() {

}

mat Icon_GL::transform() {
    return T;
}

void Icon_GL::transform(mat t) {
    T = t;
}

void Icon_GL::draw() {

    assert(m_Shader->compiled());
    m_Shader->enable();
    assert(glGetError() == GL_NO_ERROR);

    assert(m_TexCoord->created());
    glBindBuffer(GL_ARRAY_BUFFER, m_TexCoord->getId());
    GLint coordLocation = m_Shader->attributeLocation("a_coord");
    glVertexAttribPointer(coordLocation, 2, GL_FLOAT, 0, 8, 0);
    glEnableVertexAttribArray(coordLocation);
    assert(glGetError()==GL_NO_ERROR);

    assert(m_Coord->created());
    glBindBuffer(GL_ARRAY_BUFFER, m_Coord->getId());
    GLint positionLocation = m_Shader->attributeLocation("a_pos");
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, 0, 12, 0);
    glEnableVertexAttribArray(positionLocation);
    assert(glGetError()==GL_NO_ERROR);

    // do scaling
    mat S(3,3);
    eye3x3(S);
    S(0,0) = float(width()) / float(m_Texture->width());
    S(1,1) = float(height()) / float(m_Texture->height());
    T = T*S;

    GLint transformLocation = m_Shader->uniformLocation("u_T");
    glUniformMatrix3fv(transformLocation, 1, GL_FALSE, &T(0,0));
    assert(glGetError()==GL_NO_ERROR);

    assert(m_Texture->loaded());
    GLint textureLocation = m_Shader->uniformLocation("u_icon");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture->getTextureId());
    glUniform1i(textureLocation, 0);
    assert(glGetError()==GL_NO_ERROR);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    assert(glGetError()==GL_NO_ERROR);
}

const std::string Icon_GL::sc_vertexShader =
    "precision mediump float;\n"
    "attribute vec3 a_pos;\n"
    "attribute vec2 a_coord;\n"
    "varying vec2 v_coord;\n"
    "uniform mat3 u_T;\n"
    "void main() {\n"
    "   gl_Position = vec4(u_T*a_pos, 1.0);\n"
    "   v_coord = a_coord;"
    "}";

const std::string Icon_GL::sc_fragShader =
    "precision mediump float;\n"
    "varying vec2 v_coord;\n"
    "uniform sampler2D u_icon;\n"
    "void main() {\n"
    "   gl_FragColor = texture2D(u_icon, v_coord);\n"
    "}";
