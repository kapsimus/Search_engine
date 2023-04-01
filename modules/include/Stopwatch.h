#pragma once
#include <chrono>
#include <string>

class Stopwatch {
private:
    std::chrono::time_point<std::chrono::steady_clock> _beginTime;
    std::chrono::time_point<std::chrono::steady_clock> _endTime;
    bool _started = false;
public:
    Stopwatch();
    ~Stopwatch();
    void Start();
    void End(const std::string &message);
};