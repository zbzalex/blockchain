#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>

//
//
//
class ThreadPool
{
public:
    //
    //
    //
    ThreadPool(int num) : stop_(false)
    {
        for (int i = 0; i < num; i++)
        {
            workers_.emplace_back([this]
                                  {
                    while(true) {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(queue_mtx_);
                            cond_.wait(lock, [this] {
                                return stop_ || !tasks_.empty();
                            });

                            if (stop_ && tasks_.empty()) break;

                            task = std::move(tasks_.front());
                            tasks_.pop();
                        } // unlock mutex before out of scope

                        // call the task
                        task();
                        
                    } });
        }
    }

    //
    //
    //
    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queue_mtx_);
            stop_ = true;
        }

        cond_.notify_all();

        for (std::thread &worker : workers_)
        {
            worker.join();
        }
    }

    //
    //
    //
    template <class F, class... Args>
    void enqueue(F &&f, Args &&...args)
    {
        std::unique_lock<std::mutex> lock(queue_mtx_);
        tasks_.emplace([f, args...]
                       { f(args...); });

        cond_.notify_one();
    }

private:
    //
    //
    //
    std::vector<std::thread> workers_;

    //
    //
    //
    std::queue<std::function<void()>> tasks_;

    //
    //
    //
    std::mutex queue_mtx_;

    //
    //
    //
    std::condition_variable cond_;

    //
    //
    //
    bool stop_;
};

#endif // THREAD_POOL_H