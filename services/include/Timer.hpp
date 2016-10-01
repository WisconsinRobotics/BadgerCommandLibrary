#pragma once

#include <chrono>
#include <thread>


namespace BCL
{
    typedef std::chrono::milliseconds Interval;
    typedef std::function<void(void)> TimerCallback;

    class Timer
    {
    public:
        Timer();
        Timer(const Interval& timer_period, const TimerCallback& timer_callback, bool periodic = false);
        ~Timer();
        void Start();
        void Stop();
        Interval GetPeriod() const;
        void SetPeriod(const Interval& new_period);
        TimerCallback GetCallback() const;
        void SetCallback(const TimerCallback& new_callback);
        bool IsPeriodic() const;
        void SetPeriodic(bool periodic);
        bool IsRunning() const;

    private:
        void TimerWorker();

        std::thread workerThread;
        Interval period;
        TimerCallback callback;
        bool isPeriodic;
        bool isRunning;
    };
}