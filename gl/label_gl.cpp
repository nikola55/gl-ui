#include <vector>
#include <assert.h>
#include "label_gl.h"
#include "icon_gl.h"

using ui::Label;
using ui::uint;
using ui::mat;
using ui::shared_ptr;
using ui::vec2;
using ui::point;
using ui::glyph_info;

using gl::Label_GL;
using gl::VertexBuffer;
using gl::GlyphAtlas;
using gl::Drawable_GL;
using gl::ShaderProgram;
using gl::Icon_GL;

using std::string;
using std::vector;

Label_GL::Label_GL(const string &text, uint size) :
    m_Transform(3,3),
    m_Text(text),
    m_TextSize(size),
    m_Shader(new ShaderProgram(cs_VShaderSource, cs_FShaderSource)) {

    initialize();

}

void Label_GL::initialize() {

    m_GlyphAtlas = GlyphAtlas::forSize(m_TextSize);

    float atlasWidth = m_GlyphAtlas->width();
    float atlasHeight = m_GlyphAtlas->height();

    vector<GLfloat> vertexCoord(m_Text.size()*12);
    vector<GLfloat> textureCoord(m_Text.size()*12);

    size_t c = 0;
    size_t t = 0;

    float cx = 0;
    float cy = 0;

    for(size_t i = 0 ; i < m_Text.size() ; i++) {

        char cc = m_Text[i];
        glyph_info& cg = m_GlyphAtlas->info(cc);
        vec2< float >& ctc = m_GlyphAtlas->location(cc);

        GLfloat x0 = cx + cg.left;
        GLfloat y0 = cy - cg.height+cg.top;
        GLfloat x1 = x0 + cg.width;
        GLfloat y1 = y0 + cg.height;

        GLfloat tx0 = ctc.x;
        GLfloat ty0 = ctc.y;
        GLfloat tx1 = tx0+cg.width/atlasWidth;
        GLfloat ty1 = ty0+cg.height/atlasHeight;

        vertexCoord[c++] = x0; vertexCoord[c++] = y0;
        vertexCoord[c++] = x1; vertexCoord[c++] = y0;
        vertexCoord[c++] = x0; vertexCoord[c++] = y1;
        vertexCoord[c++] = x1; vertexCoord[c++] = y0;
        vertexCoord[c++] = x0; vertexCoord[c++] = y1;
        vertexCoord[c++] = x1; vertexCoord[c++] = y1;

        textureCoord[t++] = tx0; textureCoord[t++] = ty1;
        textureCoord[t++] = tx1; textureCoord[t++] = ty1;
        textureCoord[t++] = tx0; textureCoord[t++] = ty0;
        textureCoord[t++] = tx1; textureCoord[t++] = ty1;
        textureCoord[t++] = tx0; textureCoord[t++] = ty0;
        textureCoord[t++] = tx1; textureCoord[t++] = ty0;

        cx += cg.advance.x;
        cy = cg.advance.y;
    }

    width(cx);
    height(m_TextSize);

    m_VertexBuffer = VertexBuffer< GLfloat >::create( &vertexCoord[0], vertexCoord.size()*sizeof(GLfloat) );
    m_CoordBuffer = VertexBuffer< GLfloat >::create( &textureCoord[0], textureCoord.size()*sizeof(GLfloat) );

}

void Label_GL::draw() {

    assert(m_Shader->compiled());
    m_Shader->enable();
    assert(glGetError()==GL_NO_ERROR);

    assert(m_CoordBuffer->created());
    glBindBuffer(GL_ARRAY_BUFFER, m_CoordBuffer->getId());
    GLint coordLoc = m_Shader->attributeLocation("a_coord");
    assert(coordLoc != -1);
    glVertexAttribPointer(coordLoc, 2, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(coordLoc);
    assert(glGetError()==GL_NO_ERROR);

    assert(m_VertexBuffer->created());
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer->getId());
    GLint vertLoc = m_Shader->attributeLocation("a_pos");
    assert(vertLoc != -1);
    glVertexAttribPointer(vertLoc, 2, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(vertLoc);
    assert(glGetError()==GL_NO_ERROR);

    GLint TLoc = m_Shader->uniformLocation("u_T");
    assert(TLoc != -1);
    glUniformMatrix3fv(TLoc, 1, GL_FALSE, &m_Transform(0,0));
    assert(glGetError()==GL_NO_ERROR);

    assert(m_GlyphAtlas->loaded());
    GLint texLoc = m_Shader->uniformLocation("u_glyphs");
    assert(texLoc != -1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_GlyphAtlas->textureId());
    glUniform1i(texLoc, 0);
    assert(glGetError()==GL_NO_ERROR);

    glDrawArrays(GL_TRIANGLES, 0, (m_Text.size())*6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    assert(glGetError()==GL_NO_ERROR);

}

const string Label_GL::cs_VShaderSource =
        "precision mediump float;\n"
        "attribute vec2 a_pos;\n"
        "attribute vec2 a_coord;\n"
        "varying vec2 v_coord;\n"
        "uniform mat3 u_T;\n"
        "void main() {\n"
        "   gl_Position = vec4(u_T*vec3(a_pos,1.0), 1.0);\n"
        "   v_coord = a_coord;\n"
        "}\n";

const string Label_GL::cs_FShaderSource =
        "precision mediump float;\n"
        "varying vec2 v_coord;\n"
        "uniform sampler2D u_glyphs;\n"
        "void main() {\n"
        "   gl_FragColor = vec4(0,0,0,texture2D(u_glyphs, v_coord).a);\n"
        "}\n";