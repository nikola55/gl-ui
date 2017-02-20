#include "list_layout.h"

ui::uint ui::ListLayout::width_horizontal() const {
    ui::uint pad1 = padding();
    ui::uint width = pad1;
    for(uint i = 0 ; i < childrenCount() ; i++) {
        View* currChild = getChild(i);
        width += currChild->width() + pad1;
    }
    return width;
}

ui::uint ui::ListLayout::width_vertical() const {
    ui::uint pad2 = 2*padding();
    ui::uint width = 0;
    for(uint i = 0 ; i < childrenCount() ; i++) {
        View* currChild = getChild(i);
        width = std::max(width, currChild->width()+pad2);
    }
    return width;
}

ui::uint ui::ListLayout::height_horizontal() const {
    ui::uint pad2 = 2*padding();
    ui::uint height = 0;
    for(uint i = 0 ; i < childrenCount() ; i++) {
        View* currChild = getChild(i);
        height = std::max(height, currChild->height()+pad2);
    }
    return height;
}

ui::uint ui::ListLayout::height_vertical() const {
    ui::uint pad = padding();
    ui::uint height = pad;
    for(uint i = 0 ; i < childrenCount() ; i++) {
        View* currChild = getChild(i);
        height += currChild->height() + pad;
    }
    return height;
}
