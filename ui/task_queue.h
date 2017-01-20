#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H
#include <utility>
#include <queue>
#include <list>

namespace ui {

template <class Task_Type> class Fifo {

public:

    void push(const Task_Type& taskType) {
        m_taskList.push_back(taskType);
    }

    Task_Type& peek() {
        return m_taskList.front();
    }

    void pop() {
        m_taskList.pop_front();
    }

    bool empty() {
        return m_taskList.size()==0;
    }

private:
    std::list<Task_Type> m_taskList;
};

template <class Task_Type> class PriorityQueue {

public:

    void push(const Task_Type& taskType) {
        m_prioQueue.push(taskType);
    }

    Task_Type& peek() {
        return m_prioQueue.top();
    }

    void pop() {
        m_prioQueue.pop();
    }

    bool empty() {
        return m_prioQueue.empty();
    }

private:

    std::priority_queue<Task_Type> m_prioQueue;

};

template < typename Task_Type > class TaskExecutor { };

template < class Task_Type,
           template <class> class Exec_Policy = TaskExecutor,
           template <class> class Task_Holder = Fifo
          > class TaskQueue : Task_Holder<Task_Type> {

    Exec_Policy<Task_Type> m_execPolicy;

public:

    TaskQueue(const Exec_Policy<Task_Type>& execPolicy = Exec_Policy<Task_Type>()) :
        m_execPolicy(execPolicy) {

    }

    using Task_Holder<Task_Type>::push;

    void exec() {
        while(!Task_Holder<Task_Type>::empty()) {
            Task_Type& ct = Task_Holder<Task_Type>::peek();
            m_execPolicy(ct);
            Task_Holder<Task_Type>::pop();
        }
    }

};

}

#endif // TASK_QUEUE_H
