#include <unistd.h>
#include <string>
#include "channel_view.h"
#include <root_layout_gl.h>
#include <view_factory_gl.h>
#include <label.h>
#include <time.h>
#include <stdio.h>
#include <timer.h>
#include <task_queue.h>

using ui::shared_ptr;

using gl::ViewFactory_GL;
using gl::RootLayout_GL;
using ui::Icon;
using ui::Label;
using ui::ListLayout;
using ui::AbsoluteLayout;

using native::Timer;

#define BG_LOC "/home/nikola/7031585-purple-plain-background.jpg"
#define LOGO1_LOC "/home/nikola/Desktop/logo_bnt.png"
#define LOGO2_LOC "/home/nikola/Desktop/logo_btv.png"
#define TEXTBOX_LOC "/home/nikola/Desktop/text_box.png"

class TaskBase {
public:
    virtual void exec() = 0;
};

namespace ui {
template <> class TaskExecutor<TaskBase*> {
public:
    void operator()(TaskBase* tb) {
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
public:
    Update(shared_ptr<ui::View> view) : m_view(view) {
        pos.x = 0;
        pos.y = 0;
        vx = 3;
        vy = 3;
    }
    void exec() {
        pos.x+=vx;
        pos.y+=vy;
        if(pos.x+250 >= 1366 || pos.x <= 0 ) {
            vx*=-1;
        }
        if(pos.y+520 >= 768 || pos.y <= 0 ) {
            vy*=-1;
        }
        m_view->position(pos);
    }
};

class Enqueuer : public TaskBase {
    ui::TaskQueue<TaskBase*>& taskQueue;
    Update* updateTask;
    Redraw* redrawTask;
public:
    Enqueuer(ui::TaskQueue<TaskBase*>& taskQueue, shared_ptr<ui::View> view, shared_ptr<ui::View> rootView) :
        taskQueue(taskQueue),
        updateTask(new Update(view)),
        redrawTask(new Redraw(rootView)) {

    }
    ~Enqueuer() {
        delete redrawTask;
        delete updateTask;
    }

    void exec() {
        taskQueue.enqueue(redrawTask);
        taskQueue.enqueue(updateTask);
        taskQueue.enqueue(this);
    }
};


int main(int argc, char * argv[]) {

    shared_ptr<RootLayout_GL> root = RootLayout_GL::create(1366, 768);
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

    shared_ptr<AbsoluteLayout> absLayout = viewFactory->makeAbsoluteLayout();

    absLayout->addChild(icon);
    absLayout->addChild(ll);
    absLayout->addChild(text_box);

    root->addChild(absLayout);

    uint vx=3, vy=3;
    ui::point pos = { 0, 0 };

    ui::TaskQueue<TaskBase*> taskQueue;
    Enqueuer enq(taskQueue, ll, root);
    taskQueue.enqueue(&enq);
    taskQueue.exec();
}
