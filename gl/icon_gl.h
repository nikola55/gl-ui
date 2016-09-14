#ifndef ICON_GL_H
#define ICON_GL_H
#include "vertex_buffer.h"
#include "texture.h"
#include "shader_program.h"
#include "drawable_gl.h"
#include "icon.h"

namespace gl {

class Icon_GL : public ui::Icon, public Drawable_GL {

    Icon_GL(const Icon_GL &o) :
        Icon(o),
        T(3,3),
        m_TexCoord(VertexBuffer<GLfloat>::getSquareTexCoord()) {

    }

    Icon_GL& operator=(const Icon_GL &) { }

public:

    Icon_GL(const std::string &URI);

    ~Icon_GL();

    void draw();

    void transform(ui::mat);

    ui::mat transform();

private:

    ui::mat T;
    ui::shared_ptr<Texture> m_Texture;

    ui::shared_ptr<VertexBuffer<GLfloat> > m_Coord;
    ui::shared_ptr<VertexBuffer<GLfloat> > m_TexCoord;

    ui::shared_ptr<ShaderProgram> m_Shader;

    static const std::string sc_vertexShader;
    static const std::string sc_fragShader;


};

}

#endif // ICON_GL_H
