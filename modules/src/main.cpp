#include <iostream>
#include <vector>
#include <string>
#include "nlohmann/json.hpp"
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include "ConfigException.h"


int main() {
    ConverterJSON conv;
    InvertedIndex index;
    int responseLimit = 0;
    try {
        conv.NormalizeDocuments();
        responseLimit = conv.GetResponsesLimit();
        std::vector<std::string> requests = conv.GetRequests();
        index.UpdateDocumentBase(conv.GetTextDocuments());
    }
    catch (const ConfigException &ex) {
        std::cerr << ex.getMessage();
    }
    std::vector<Entry> wordsCount = index.GetWordCount("123");
    SearchServer server(index);
    std::vector<std::vector<RelativeIndex>> answers = server.search(conv.GetRequests());
    conv.putAnswers(answers);
    return 0;
}
