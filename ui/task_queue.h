#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H
#include <utility>
#include <list>

#include "task.h"

namespace ui {

template < class Task_Type,
           template <class> class Exec_Policy = TaskExecutor
          > class TaskQueue {

    std::list<Task_Type> m_taskQueue;
    Exec_Policy<Task_Type> m_execPolicy;

public:

    TaskQueue(const Exec_Policy<Task_Type>& execPolicy = Exec_Policy<Task_Type>()) :
        m_execPolicy(execPolicy) {

    }

    void enqueue(const Task_Type& task) {
        m_taskQueue.push_back(task);
    }

    void exec() {

        while(!m_taskQueue.empty()) {
            Task_Type& ct = m_taskQueue.front();
            m_execPolicy(ct);
            m_taskQueue.pop_front();
        }

    }

};

}

#endif // TASK_QUEUE_H
