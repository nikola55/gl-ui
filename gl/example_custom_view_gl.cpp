#include "example_custom_view_gl.h"

using gl::ExampleCustomView_GL;
using gl::Drawable_GL;
using gl::Icon_GL;
using gl::Label_GL;

using ui::View;
using ui::shared_ptr;
using ui::uint;
using ui::mat;

using std::string;

ExampleCustomView_GL::ExampleCustomView_GL(
        const string &iconURI,
        const string text,
        uint textSize,
        TextPosition textPos) :
    m_Transform(3,3),
    m_TextPosition(textPos) {

    m_Label = new Label_GL(text, textSize);
    m_Icon = new Icon_GL(iconURI);

}

void ExampleCustomView_GL::draw() {

    mat T = transform();

    m_Icon->transform(T);

    mat TransLabel(3,3);
    ui::eye3x3(TransLabel);
    ui::trans3x3(TransLabel, m_Icon->width(), m_Icon->height()/2.0 - m_Label->height()/2);
    mat TLabel = T*TransLabel;
    m_Label->transform(TLabel);

    m_Label->draw();
    m_Icon->draw();


}
