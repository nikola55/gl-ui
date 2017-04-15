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
using ui::Icon;
using ui::Label;
using ui::ListLayout;
using ui::AbsoluteLayout;

using native::Timer;

#define BG_LOC "/home/nikola/Downloads/ws_Green_Gradient_Background_1366x768.jpg"
//#define LOGO1_LOC "/home/nikola/Desktop/logo_bnt.png"
//#define LOGO2_LOC "/home/nikola/Desktop/logo_btv.png"
//#define TEXTBOX_LOC "/home/nikola/Desktop/text_box.png"
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
    shared_ptr<ui::View> m_mouseView;
public:

    ReadMouse(shared_ptr<ui::View> mouseView) :
        m_mouseView(mouseView) {


    }

    ~ReadMouse() {
    }

    void exec() {
        SDL_Event evt;
        while(SDL_PollEvent(&evt)) {
            if(evt.type==SDL_MOUSEMOTION) {
                ui::point p = m_mouseView->position();
                p.x+=evt.motion.xrel;
                p.y-=evt.motion.yrel;
                m_mouseView->position(p);
            }
        }
    }

};

class Enqueuer : public TaskBase {
    ui::TaskQueue<TaskBase*>& taskQueue;
    std::list<TaskBase*> m_taskList;
public:
    Enqueuer(ui::TaskQueue<TaskBase*>& taskQueue, shared_ptr<ui::View> rootView) :
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
    shared_ptr<ViewFactory_GL> viewFactory = new ViewFactory_GL;
    shared_ptr<ui::Layout> root = viewFactory->makeRootLayout(0, 0, 1366, 768);
    shared_ptr<Icon> icon = viewFactory->makeIcon(BG_LOC);
    shared_ptr<AbsoluteLayout> absLayout = viewFactory->makeAbsoluteLayout();
    absLayout->addChild(icon);
    root->addChild(absLayout);
    ui::TaskQueue<TaskBase*> taskQueue;
    Enqueuer enq(taskQueue, root);
//    enq.addTask(new Update(ll));
    enq.addTask(new Redraw(root));
//    enq.addTask(new ReadMouse(mouse));
    taskQueue.push(&enq);
    taskQueue.exec();
}
