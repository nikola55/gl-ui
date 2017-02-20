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

    Label_GL(const std::wstring &text, ui::uint size);

    const std::wstring& text() const { return m_text; }

    void text(const std::wstring &text) {
        m_text = text;
        changed(true);
        initialize();
    }

    void width(ui::uint) { } // cannot change width

    void height(ui::uint) { } // cannot change height

    ui::uint size() const { return m_textSize; }

    void size(ui::uint s) {
        m_textSize = s;
        changed(true);
        initialize();
    }

    void transform(const ui::mat3& T) {
        m_transform = T;
    }

    void text_color(ui::byte r, ui::byte g, ui::byte b) {
        m_color[0] = r/255.f;
        m_color[1] = g/255.f;
        m_color[2] = b/255.f;
        changed(true);
    }

    const ui::mat3& transform() const { return m_transform; }

    void draw();

protected:

    void initialize();

private:

    ui::mat3 m_transform;
    std::wstring m_text;
    ui::uint m_textSize;
    ui::shared_ptr< ShaderProgram > m_shader;
    ui::shared_ptr< VertexBuffer<GLfloat> > m_vertexBuffer;
    ui::shared_ptr< VertexBuffer<GLfloat> > m_coordBuffer;
    ui::shared_ptr< GlyphAtlas > m_glyphAtlas;

    float m_color[3];

    static const std::string sc_vertexShader;
    static const std::string sc_fragmentShader;

};

}

#endif // LABEL_GL_H
