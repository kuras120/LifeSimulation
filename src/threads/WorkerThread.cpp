//
// Created by root on 16.06.18.
//

#include "WorkerThread.h"

WorkerThread::WorkerThread()
{
    thread.reset(new std::thread([this]
    {
        this->isRunning = true;
        this->startThread();
    }));
}

WorkerThread::~WorkerThread() {
    {
        isRunning = false;
        itemInQueue.notify_one();
    }
    thread->join();
}

void WorkerThread::startThread()
{
    std::unique_lock<std::mutex> l(mutex);

    do
    {
        while (isRunning && tasks.empty())
            itemInQueue.wait(l);

        while (!tasks.empty())
        {
            const std::function<void()> t = tasks.front();
            tasks.pop_front();
            l.unlock();
            t();
            l.lock();
        }
        itemInQueue.notify_all();

    } while (isRunning);
    itemInQueue.notify_all();
}

void WorkerThread::addTask(const std::function<void()> &t) {
    std::lock_guard<std::mutex> mtx(mutex);
    tasks.push_back(t);
    itemInQueue.notify_one();
}

void WorkerThread::addTaskAtFront(const std::function<void()> &t) {
    std::lock_guard<std::mutex> mtx(mutex);
    tasks.push_front(t);
    itemInQueue.notify_one();
}
