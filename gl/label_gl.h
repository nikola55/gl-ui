#ifndef LABEL_GL_H
#define LABEL_GL_H

#include "label.h"
#include "drawable_gl.h"

namespace gl {

class Label_GL : public ui::Label, public Drawable_GL {

public:

    Label_GL();

    ~Label_GL();

    const std::string& text() const { return m_Text; }

    void text(const std::string &text) {
        m_Text = text;
        m_Changed = true;
    }

    ui::uint size() const { return m_TextSize; }

    void size(ui::uint s) {
        m_TextSize = s;
        m_Changed = true;
    }

    void transform(ui::mat T) {
        m_Transform = T;
    }

    ui::mat transform() { return m_Transform; }

    void draw();

private:
    ui::mat m_Transform;
    std::string m_Text;
    ui::uint m_TextSize;
    bool m_Changed;

};

}

#endif // LABEL_GL_H
