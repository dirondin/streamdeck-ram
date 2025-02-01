#include "ThreadTimer.h"

ThreadTimer::ThreadTimer()
    : Running(false)
{
}

ThreadTimer::~ThreadTimer()
{
    if (Running.load(std::memory_order_acquire))
    {
        Stop();
    };
}

void ThreadTimer::Start(int interval, std::function<void(void)> func)
{
    if (Running.load(std::memory_order_acquire))
    {
        Stop();
    };

    Running.store(true, std::memory_order_release);
    Thread = std::thread([this, interval, func]()
                         {
        while (Running.load(std::memory_order_acquire))
        {
            func();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        } });
}

void ThreadTimer::Stop()
{
    Running.store(false, std::memory_order_release);
    if (Thread.joinable())
    {
        Thread.join();
    }
}

bool ThreadTimer::IsRunning() const noexcept
{
    return Running.load(std::memory_order_acquire) && Thread.joinable();
}
