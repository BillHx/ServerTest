#include "../include/threadpool.h"

ThreadPool::ThreadPool(int thread_num):m_stop(false), m_thread_num(thread_num)
{
    for (int i = 0; i < m_thread_num; ++i) {
        if (pthread_create(&m_threads[i], NULL, doTask, this) != 0)
        {
            // exception
        }

        // 线程脱离，让线程自己控制同步，控制资源释放
        if (pthread_detach(m_threads[i]) != 0)
        {
            // exception
        }
    }
}

ThreadPool::~ThreadPool()
{
    memset(m_threads, 0, MAX_THREAD_CNT); 
    m_stop = true;
}

int ThreadPool::addTask(Task task)
{
    m_lock.lock();
    if (m_task_queue.size() >= MAX_TASK_CNT)
    {
        return 1;
    }
    m_task_queue.push_back(task);
    m_lock.unlock();

    m_sem.post();
    return 0;
}

void* ThreadPool::doTask(void *arg)
{
    ThreadPool *self = (ThreadPool *)arg;

    self->work();

    return arg;
}

void ThreadPool::work()
{
    // 若存在任务可读，则执行任务
    m_sem.wait();
    m_lock.lock();
    if (m_task_queue.empty())
    {
        m_lock.unlock();
        return;
    }

    Task myTask = m_task_queue.front();
    m_task_queue.pop_front();
    m_lock.unlock();

    myTask.run();

    return ;
}

