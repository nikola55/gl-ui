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

    Icon_GL(const std::string &URI);

    void draw();

    void transform(ui::mat3);

    ui::mat3 transform();

private:

    ui::mat3 m_Transformation;
    ui::shared_ptr<Texture> m_Texture;

    ui::shared_ptr< VertexBuffer<GLfloat> > m_Coord;
    ui::shared_ptr< VertexBuffer<GLfloat> > m_TexCoord;

    ui::shared_ptr<ShaderProgram> m_Shader;

    static const std::string sc_VertexShader;
    static const std::string sc_FragShader;


};

}

#endif // ICON_GL_H
