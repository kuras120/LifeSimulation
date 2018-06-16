//
// Created by root on 16.06.18.
//

#ifndef LIFESIMULATION_WORKERTHREAD_H
#define LIFESIMULATION_WORKERTHREAD_H


#include <functional>
#include <condition_variable>
#include <thread>
#include <list>

class WorkerThread {
public:
    WorkerThread();
    ~WorkerThread();
    void addTask(const std::function<void()>& t);
    void addTaskAtFront(const std::function<void()>& t);
private:
    void startThread();
private:
    std::unique_ptr<std::thread> thread;
protected:
    std::mutex mutex;
    bool isRunning = true;
    std::condition_variable itemInQueue;
    std::condition_variable queueEmpty;
    std::list<std::function<void()>> tasks;
};


#endif //LIFESIMULATION_WORKERTHREAD_H
