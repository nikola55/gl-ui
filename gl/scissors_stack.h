#ifndef SCISSORSSTACK_H
#define SCISSORSSTACK_H
#include <list>
#include <GLES2/gl2.h>
#include "ui_common.h"

namespace gl {

class ScissorsStack {

private:

    ui::uint size() const { return m_Stack.size(); }

    ui::grid<ui::uint> pop() {
        m_Stack.pop_back();
        ui::grid<ui::uint> &rect = m_Stack.back();
        glScissor(rect(0,0), rect(0,1), rect(1,0), rect(1,1));
    }

    void push(ui::grid<ui::uint> rect) {
        glScissor(rect(0,0), rect(0,1), rect(1,0), rect(1,1));
        m_Stack.push_back(rect);
    }

private:
    std::list< ui::grid<ui::uint> > m_Stack;
};

}

#endif // SCISSORSSTACK_H
