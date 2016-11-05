#ifndef EXAMPLECUSTOMVIEW_GL_H
#define EXAMPLECUSTOMVIEW_GL_H
#include "drawable_gl.h"
#include "rectangle_base_view.h"
#include "icon_gl.h"
#include "label_gl.h"

namespace gl {

class ExampleCustomView_GL : public ui::RectangleBaseView, public Drawable_GL {

public:

    enum TextPosition {
        LEFT,
        RIGHT,
        ABOVE,
        BELOW
    };

    ExampleCustomView_GL(const std::string &iconURI, const std::wstring text, ui::uint textSize, TextPosition textPos);

    void draw();

    void transform(ui::mat3 T) { m_Transform = T; }

    ui::mat3 transform() { return m_Transform; }

    void width(ui::uint w) {
        m_Icon->width(w);
        RectangleBaseView::width(w);
    }

    void height(ui::uint h) {
        m_Icon->height(h);
        RectangleBaseView::height(h);
    }

    void color(ui::byte r, ui::byte g, ui::byte b) {
        m_Label->text_color(r,g,b);
    }

private:
    ui::shared_ptr<Icon_GL> m_Icon;
    ui::shared_ptr<Label_GL> m_Label;
    ui::mat3 m_Transform;
    TextPosition m_TextPosition;
};

}

#endif // EXAMPLECUSTOMVIEW_GL_H
