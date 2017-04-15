#include "view.h"


ui::View::View() : m_parent(0) {

}

void ui::View::setParent(ui::View *p) {
    m_parent = p;
}

ui::View *ui::View::getParent() {
    return m_parent;
}

ui::View::~View() { }
