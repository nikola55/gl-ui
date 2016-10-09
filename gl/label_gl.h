#ifndef LABEL_GL_H
#define LABEL_GL_H

#include "label.h"
#include "drawable_gl.h"
#include "vertex_buffer.h"
#include "glyph_atlas.h"
#include "shader_program.h"

namespace gl {

class Label_GL : public ui::Label, public Drawable_GL {

public:

    Label_GL(const std::string &text, ui::uint size);

    const std::string& text() const { return m_Text; }

    void text(const std::string &text) {
        m_Text = text;
        initialize();
    }

    ui::uint size() const { return m_TextSize; }

    void size(ui::uint s) {
        m_TextSize = s;
        initialize();
    }

    void transform(ui::mat T) {
        m_Transform = T;
    }

    void color(ui::byte r, ui::byte g, ui::byte b) {
        m_Color[0] = r/255.f;
        m_Color[1] = g/255.f;
        m_Color[2] = b/255.f;
    }

    ui::mat transform() { return m_Transform; }

    void draw();

protected:

    void initialize();

private:

    ui::mat m_Transform;
    std::string m_Text;
    ui::uint m_TextSize;
    ui::shared_ptr< ShaderProgram > m_Shader;
    ui::shared_ptr< VertexBuffer<GLfloat> > m_VertexBuffer;
    ui::shared_ptr< VertexBuffer<GLfloat> > m_CoordBuffer;
    ui::shared_ptr< GlyphAtlas > m_GlyphAtlas;

    float m_Color[3];

    static const std::string cs_VShaderSource;
    static const std::string cs_FShaderSource;

};

}

#endif // LABEL_GL_H
