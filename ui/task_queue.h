#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H
#include <utility>
#include <list>

#include "task.h"

namespace ui {

template < class Task_Type, class Exec_Policy = TaskExecutor<Task_Type> > class TaskQueue {

    typedef std::pair<Task_Type, Exec_Policy> Task;

    std::list<Task> m_taskQueue;

public:

    void enqueue(Task_Type task, Exec_Policy policy = Exec_Policy()) {
        m_taskQueue.push_back(std::make_pair(task, policy));
    }

    void exec() {

        while(!m_taskQueue.empty()) {
            Task& ct = m_taskQueue.back();
            Exec_Policy& execPolicy = ct.second;
            Task_Type& task = ct.first;
            execPolicy(task);
            m_taskQueue.pop_back();
        }

    }

};

}

#endif // TASK_QUEUE_H
