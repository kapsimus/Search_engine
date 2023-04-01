#pragma once
#include <chrono>
#include <string>

class Stopwatch {
private:
    std::chrono::time_point<std::chrono::steady_clock> beginTime;
    std::chrono::time_point<std::chrono::steady_clock> endTime;
    bool started = false;
public:
    Stopwatch();
    ~Stopwatch();
    void Start();
    void End(const std::string &message);
};