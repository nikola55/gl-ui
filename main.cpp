#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string>
#include "channel_view.h"
#include <root_layout_sdl.h>
#include <view_factory_gl.h>
#include <list_layout.h>
#include <label.h>
#include <time.h>
#include <stdio.h>
#include <timer.h>
#include <list>
#include <task_queue.h>

using ui::shared_ptr;

using gl::ViewFactory_GL;
using gl::RootLayout_SDL;
using ui::Icon;
using ui::Label;
using ui::ListLayout;
using ui::AbsoluteLayout;

using native::Timer;

#define BG_LOC "7031585-purple-plain-background.jpg"
#define LOGO1_LOC "/home/nikola/Desktop/logo_bnt.png"
#define LOGO2_LOC "/home/nikola/Desktop/logo_btv.png"
#define TEXTBOX_LOC "/home/nikola/Desktop/text_box.png"
#define MOUSE_POINTER "082745-grunge-brushed-metal-pewter-icon-business-cursor.png"

class TaskBase {
public:
    virtual void exec() = 0;
};

namespace ui {
template <> class TaskExecutor<TaskBase*> {
public:
    void execute(TaskBase* tb) {
        tb->exec();
    }
};
}

class Redraw : public TaskBase {
    shared_ptr<ui::View> m_rootView;
public:
    Redraw(shared_ptr<ui::View> rootView) :
        m_rootView(rootView) {

    }
    void exec() {
        Timer t;
        m_rootView->draw();
    }
};

class Update : public TaskBase {
    shared_ptr<ui::View> m_view;
    ui::point pos;
    uint vx;
    uint vy;
    uint vwidth;
    uint vheight;
public:
    Update(shared_ptr<ui::View> view) : m_view(view) {
        pos.x = 0;
        pos.y = 0;
        vx = 3;
        vy = 3;
        vwidth = m_view->width();
        vheight = m_view->height();
    }
    void exec() {
        pos.x+=vx;
        pos.y+=vy;
        if(pos.x+vwidth >= 1366 || pos.x <= 0 ) {
            vx*=-1;
        }
        if(pos.y+vheight >= 768 || pos.y <= 0 ) {
            vy*=-1;
        }
        m_view->position(pos);
    }
};

class ReadMouse : public TaskBase {
    const std::string m_mouseFile;
    input_event m_inputEvent;
    int m_absX;
    int m_absY;
    int m_mouseFd;
    shared_ptr<ui::View> m_mouseView;
public:

    ReadMouse(const std::string& mouseFile, shared_ptr<ui::View> mouseView) :
        m_mouseFile(mouseFile),
        m_absX(0),
        m_absY(0),
        m_mouseFd(0),
        m_mouseView(mouseView) {

        if((m_mouseFd=open(m_mouseFile.c_str(), O_RDONLY|O_NONBLOCK))!=-1) {
            // opened
        }

    }

    ~ReadMouse() {
        if(m_mouseFd != -1)
            close(m_mouseFd);
    }

    void exec() {
        if(read(m_mouseFd, &m_inputEvent, sizeof(m_inputEvent))!=-1) {
            uint8_t *ptr = reinterpret_cast<uint8_t*>(&m_inputEvent);
            uint8_t button = ptr[0];
            bool lClick = button & 0x1;
            bool rClick = 0 < (button & 0x2);
            bool mClick = 0 < (button & 0x4);
            int8_t relX = ptr[1];
            int8_t relY = ptr[2];
            m_absX += relX;
            m_absY += relY;
            if(m_absX > 0 && m_absY > 0) {
                ui::point p = { m_absX, m_absY };
                m_mouseView->position(p);
            }
        }
    }

};

class Enqueuer : public TaskBase {
    ui::TaskQueue<TaskBase*>& taskQueue;
    std::list<TaskBase*> m_taskList;
    Timer *timer;
public:
    Enqueuer(ui::TaskQueue<TaskBase*>& taskQueue, shared_ptr<ui::View> view, shared_ptr<ui::View> rootView) :
        taskQueue(taskQueue) {
    }
    ~Enqueuer() {
    }
    void addTask(TaskBase *task) {
        m_taskList.push_back(task);
    }
    void exec() {
        for(std::list<TaskBase*>::iterator i = m_taskList.begin() ; i!= m_taskList.end() ;i++) {
            taskQueue.push(*i);
        }
        taskQueue.push(this);
    }
};

int main(int argc, char * argv[]) {
    ui::point rl_pos = {0,0};
    shared_ptr<RootLayout_SDL> root = RootLayout_SDL::create(rl_pos, 1366, 768);
    shared_ptr<ViewFactory_GL> viewFactory = new ViewFactory_GL;
    shared_ptr<ChannelView> chView = new ChannelView(L"БНТ 1 HD", L"15:30 - 16:30 Още от деня на изборите", LOGO1_LOC);
    shared_ptr<ChannelView> chView2 = new ChannelView(L"bTV HD", L"15:30 - 16:30 Студио Избори 2016", LOGO2_LOC);
    shared_ptr<ListLayout> ll = viewFactory->makeListLayout(false);

    shared_ptr<Icon> text_box = viewFactory->makeIcon(TEXTBOX_LOC);
    ui::point tpos = { (1366-text_box->width())/2, 768 - 100 };
    text_box->position(tpos);

    ll->addChild(chView2);
    ll->addChild(chView);
    ll->addChild(chView2);
    ll->addChild(chView);
    ll->addChild(chView2);
    ll->addChild(chView);
    ll->padding(2);

    shared_ptr<Icon> icon = viewFactory->makeIcon(BG_LOC);
    shared_ptr<Icon> mouse = viewFactory->makeIcon(MOUSE_POINTER);

    shared_ptr<AbsoluteLayout> absLayout = viewFactory->makeAbsoluteLayout();

    absLayout->addChild(icon);
    absLayout->addChild(ll);
    absLayout->addChild(text_box);
    absLayout->addChild(mouse);

    root->addChild(absLayout);


    ui::TaskQueue<TaskBase*> taskQueue;
    Enqueuer enq(taskQueue, ll, root);
    enq.addTask(new Update(ll));
    enq.addTask(new Redraw(root));
//    enq.addTask(new ReadMouse("/dev/input/mouse0", mouse));
    taskQueue.push(&enq);
    taskQueue.exec();
}
