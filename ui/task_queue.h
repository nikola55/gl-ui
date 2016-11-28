#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H
#include <utility>
#include <list>

#include "task.h"

namespace ui {

template < class Task_Type, class Exec_Policy = TaskExecutor<Task_Type> > class TaskQueue {

    std::list<Task_Type> m_taskQueue;
    Exec_Policy m_execPolicy;

public:

    TaskQueue(const Exec_Policy& execPolicy = Exec_Policy()) :
        m_execPolicy(execPolicy) {

    }

    void enqueue(const Task_Type& task) {
        m_taskQueue.push_back(task);
    }

    void exec() {

        while(!m_taskQueue.empty()) {
            Task_Type& ct = m_taskQueue.back();
            m_execPolicy(ct);
            m_taskQueue.pop_back();
        }

    }

};

}

#endif // TASK_QUEUE_H
