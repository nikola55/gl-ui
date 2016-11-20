#include "channel_view.h"
#include <cassert>

using ui::shared_ptr;
using ui::point;
using ui::mat3;

using gl::Texture;
using gl::Label_GL;
using gl::Icon_GL;

ui::shared_ptr<gl::Icon_GL> ChannelView::s_background;

#define CHBG_LOC "/home/nikola/Desktop/bg_grad.png"

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
        s_background = new Icon_GL(CHBG_LOC);
    }

    width(s_background->width());
    height(s_background->height());
    margin(0);
    padding(0);

    addChild(s_background);
    addChild(m_epg);
    addChild(m_title);
    addChild(m_channelIcon);

    GLuint frame;
    glGenFramebuffers(1, &frame);
    glBindFramebuffer(GL_FRAMEBUFFER, frame);
    assert(glGetError() == GL_NO_ERROR);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width(), height(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    assert(glGetError() == GL_NO_ERROR);
    GLuint depth;
    glGenRenderbuffers(1, &depth);
    glBindRenderbuffer(GL_RENDERBUFFER, depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width(), height());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);
    assert(glGetError() == GL_NO_ERROR);

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    mat3 prev = m_transform;
    mat3 T;
    T(0,0) = (2.0/float(width())); T(0, 1) = 0.0; T(0, 2) = -1.0;
    T(1,0) = 0.0; T(1, 1) = (2.0/float(height())); T(1, 2) = -1.0;
    T(2,0) = 0.0; T(2, 1) = 0.0; T(2,2) = 1.0;
    mat3 inv_y;
    eye3x3(inv_y);
    inv_y(1,1)=-1;
    inv_y(1,2)=height();
    m_transform = T*inv_y;

    glViewport(0, 0, width(), height());
    AbsoluteLayout_GL::draw();

    m_cached = new Icon_GL(new Texture(texture, width(), height()));

    m_transform = prev;

    glDeleteRenderbuffers(1, &depth);
    glDeleteFramebuffers(1, &frame);
}

void ChannelView::draw() {
    m_cached->transform(m_transform);
    m_cached->draw();
}
