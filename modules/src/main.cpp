#include <iostream>
#include <vector>
#include <string>
#include "nlohmann/json.hpp"
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"


int main() {
    ConverterJSON conv;
    InvertedIndex index;
    int responseLimit = conv.GetResponsesLimit();
    std::vector<std::string> requests = conv.GetRequests();
    index.UpdateDocumentBase(conv.GetTextDocuments());
    std::vector<Entry> wordsCount = index.GetWordCount("123");
    SearchServer server(index);
    server.search(conv.GetRequests());
    std::vector<std::vector<std::pair<int, float>>> answers{{{1, 0.99},{2, 0.88}},{}};
    conv.putAnswers(answers);
    std::cout << "response limit: " << responseLimit << std::endl;
    return 0;
}
