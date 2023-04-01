#include <iostream>
#include "Stopwatch.h"

Stopwatch::Stopwatch()  {
    beginTime = std::chrono::steady_clock::now();
    endTime = beginTime;
}

Stopwatch::~Stopwatch() {
    if (!started) {
        End("Module elapsed:");
    }
}

void Stopwatch::Start() {
    beginTime = std::chrono::steady_clock::now();
    endTime = beginTime;
    started = true;
}

void Stopwatch::End(const std::string &message) {
    endTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime);
    std::cout << message << " " << elapsed.count() << " millisecond" << std::endl;
}