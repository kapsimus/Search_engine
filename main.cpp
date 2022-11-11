#include <iostream>
#include <vector>
#include <string>
#include "nlohmann/json.hpp"
#include "ConverterJSON.h"

int main() {
    ConverterJSON conv;
    int responseLimit = conv.GetResponsesLimit();
    std::vector<std::string> requests = conv.GetRequests();
    std::cout << responseLimit << std::endl;
    return 0;
}
