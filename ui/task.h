#ifndef TASK_H
#define TASK_H

namespace ui {

template < typename Task_Type > class TaskExecutor {
public:
    void operator()(Task_Type &tt) {
        tt();
    }
};

}

#endif // TASK_H
