#ifndef ICON_GL_H
#define ICON_GL_H
#include "vertex_buffer.h"
#include "texture.h"
#include "shader_program.h"
#include "drawable_gl.h"
#include "icon.h"

namespace gl {

class Icon_GL : public ui::Icon, public Drawable_GL {

public:

    Icon_GL(ui::shared_ptr<Texture>);

    Icon_GL(const std::string &URI);

    void draw();

    void transform(const ui::mat3& t) { m_transf = t; }

    const ui::mat3& transform() const { return m_transf; }

private:

    ui::mat3 m_transf;
    ui::shared_ptr<Texture> m_texture;

    ui::shared_ptr< VertexBuffer<GLfloat> > m_coord;
    ui::shared_ptr< VertexBuffer<GLfloat> > m_texCoord;

    ui::shared_ptr<ShaderProgram> m_shader;

    static const std::string sc_vertexShader;
    static const std::string sc_fragShader;

};

}

#endif // ICON_GL_H
