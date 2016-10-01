#include "Timer.hpp"

using namespace BCL;


Timer::Timer()
{
    this->period = Interval(0);
    this->callback = nullptr;
    this->isPeriodic = false;
}

Timer::Timer(const Interval& timer_period, const TimerCallback& timer_callback, bool periodic)
{
    this->period = timer_period;
    this->callback = timer_callback;
    this->isPeriodic = periodic;
}

Timer::~Timer()
{
    this->Stop();
}

void Timer::Start()
{
    this->isRunning = true;
    this->workerThread = std::thread(&Timer::TimerWorker, this);
}

void Timer::Stop()
{
    if (!this->isRunning)
        return;
        
    this->isRunning = false;
    if (this->workerThread.joinable())
        this->workerThread.join();
}

Interval Timer::GetPeriod() const
{
    return this->period;
}

void Timer::SetPeriod(const Interval& new_period)
{
    this->period = new_period;
}

TimerCallback Timer::GetCallback() const
{
    return this->callback;
}

void Timer::SetCallback(const TimerCallback& new_callback)
{
    this->callback = new_callback;
}

bool Timer::IsPeriodic() const
{
    return this->isPeriodic;
}

void Timer::SetPeriodic(bool periodic)
{
    this->isPeriodic = periodic;
}

bool Timer::IsRunning() const
{
    return this->isRunning;
}

void Timer::TimerWorker()
{
     bool timeout = false;

     auto start = std::chrono::system_clock::now();

     while (!timeout && this->isRunning)
     {
        auto current = std::chrono::system_clock::now();
        if (current - start < this->period)
            continue;
        
        this->callback();

        timeout = !this->isPeriodic;
        start = std::chrono::system_clock::now();
     }

     this->isRunning = false;
}