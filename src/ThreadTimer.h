#pragma once

#include <atomic>
#include <thread>
#include <functional>

class ThreadTimer
{
public:
    ThreadTimer();
    ~ThreadTimer();

    bool IsRunning() const noexcept;

    void Start(int interval, std::function<void(void)> func);
    void Stop();

private:
    std::atomic<bool> Running;
    std::thread Thread;
};
