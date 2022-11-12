#include <iostream>
#include <vector>
#include <string>
#include "nlohmann/json.hpp"
#include "ConverterJSON.h"

int main() {
    ConverterJSON conv;
    int responseLimit = conv.GetResponsesLimit();
    std::vector<std::string> requests = conv.GetRequests();
    std::vector<std::string> docs = conv.GetTextDocuments();
    std::vector<std::vector<std::pair<int, float>>> answers{{{1, 0.99},{2, 0.88}},{}};
    conv.putAnswers(answers);
    std::cout << responseLimit << std::endl;
    return 0;
}
