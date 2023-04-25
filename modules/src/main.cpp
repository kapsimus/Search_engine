#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "nlohmann/json.hpp"
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include "ConfigException.h"
#include "Stopwatch.h"


int main() {
    ConverterJSON conv;
    InvertedIndex index;
    Stopwatch timer;
    timer.Start();
    try {
        conv.NormalizeDocuments();
        std::vector<std::string> requests = conv.GetRequests();
        index.UpdateDocumentBase(conv.GetTextDocuments());
    }
    catch (const ConfigException &ex) {
        std::cerr << ex.getMessage();
    }
    std::vector<Entry> wordsCount = index.GetWordCount("123");
    SearchServer server(index);
    std::vector<std::vector<RelativeIndex>> answers = server.search(conv.GetRequests());
    conv.PutAnswers(answers);
    timer.End("main elapsed:");
    return 0;
}
