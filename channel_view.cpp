#include "channel_view.h"

using ui::shared_ptr;
using ui::point;

using gl::Label_GL;
using gl::Icon_GL;

ui::shared_ptr<gl::Icon_GL> ChannelView::s_background;

ChannelView::ChannelView(const std::wstring &title, const std::wstring &epg, const std::string &iconPath) {

    m_channelIcon = new Icon_GL(iconPath);

    m_title = new Label_GL(title, 25);
    m_title->text_color(203, 203, 203);

    m_epg = new Label_GL(epg, 13);
    point epgPos = { 15, 10 };
    m_epg->position(epgPos);

    point iconPos = { 15, 30 };
    m_channelIcon->position(iconPos);

    point titlePos = { 15+m_channelIcon->width()+15, (iconPos.y+iconPos.y+m_channelIcon->height()-m_channelIcon->height())/2 };
    m_title->position(titlePos);

    if(s_background == 0) {
        s_background = new Icon_GL("/home/nikola/Desktop/bg_grad.png");
    }

    width(s_background->width());
    height(s_background->height());
    margin(0);
    padding(0);

    addChild(s_background);
    addChild(m_epg);
    addChild(m_title);
    addChild(m_channelIcon);
}
