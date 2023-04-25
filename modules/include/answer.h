#pragma once
#include <string>

struct Answer {
    std::string requestId;
    bool result;
    int docId;
    double rank;
};
