#include <iostream>
#include "Stopwatch.h"

Stopwatch::Stopwatch()  {
    _beginTime = std::chrono::steady_clock::now();
    _endTime = _beginTime;
}

Stopwatch::~Stopwatch() {
    if (!_started) {
        End("Module elapsed:");
    }
}

void Stopwatch::Start() {
    _beginTime = std::chrono::steady_clock::now();
    _endTime = _beginTime;
    _started = true;
}

void Stopwatch::End(const std::string &message) {
    _endTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _beginTime);
    std::cout << message << " " << elapsed.count() << " millisecond" << std::endl;
}