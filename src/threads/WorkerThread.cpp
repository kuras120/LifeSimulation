//
// Created by root on 16.06.18.
//

#include "WorkerThread.hpp"
#include "../output/Logger.h"

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

        queueEmpty.notify_one();

        while (!tasks.empty())
        {
            Logger::Instance()->Save("task queue size: " + std::to_string(tasks.size()));

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

/*
 * example:
 *
 * void s(){
    for(int i =0; i<400; i++)
        logger->Save(std::to_string(i));
    }

    void c(){
        logger->Save("xxx");
    }

 * WorkerThread thread;
 * auto x = (const std::function<void()> &)s;
 * auto d = (const std::function<void()> &)c;
 *
 * thread.addTask(x);
 * thread.addTask(x);
 * thread.addTaskAtFront(d);
 *
 *
 * thread.addTask((const std::function<void()> &) []{
 *       std::cout << "second";
 *  });
 *
 */
