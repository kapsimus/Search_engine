#include <iostream>
#include "nlohmann/json.hpp"
#include "ConverterJSON.h"

int main() {
    ConverterJSON conv;
    int responseLimit = conv.GetResponsesLimit();
    std::cout << responseLimit << std::endl;
    return 0;
}
