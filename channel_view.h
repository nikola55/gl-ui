#ifndef CHANNELVIEW_H
#define CHANNELVIEW_H

#include <string>
#include <label_gl.h>
#include <icon_gl.h>
#include <absolute_layout_gl.h>

class ChannelView : public gl::AbsoluteLayout_GL {

public:

    ChannelView(const std::wstring &title, const std::wstring &epg, const std::string &iconPath);

    void draw();

private:
    ui::shared_ptr<gl::Icon_GL> m_cached;
    ui::shared_ptr<gl::Label_GL> m_title;
    ui::shared_ptr<gl::Label_GL> m_epg;
    ui::shared_ptr<gl::Icon_GL> m_channelIcon;
    static ui::shared_ptr<gl::Icon_GL> s_background;
};

#endif // CHANNELVIEW_H
