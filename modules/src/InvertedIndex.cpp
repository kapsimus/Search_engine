#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <sstream>
#include <map>
#include "InvertedIndex.h"



void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    const unsigned int MIN_THREAD_COUNT = 8;
    std::mutex mutex;
    if (!input_docs.empty()) {
        for (int i = 0; i < input_docs.size(); ++i) {
            std::ifstream file(input_docs[i]);
            if (file.is_open()) {
                auto ss = std::ostringstream{};
                ss << file.rdbuf();
                docs.push_back(ss.str());
            } else {
                std::cout << "Unable to open file " << input_docs[i] << std::endl;
            }
            file.close();
        }
    } else return;

    auto task = [&mutex]
            (size_t& _id,
            std::map<std::string, std::vector<Entry>>& _freq_dictionary,
            std::vector<std::string>& _docs) {
        mutex.lock();
        int currentId(_id);
        _id++;
        mutex.unlock();
        if (currentId >= _docs.size()) {
            return;
        }
        std::string text = _docs[currentId];
        std::string word;
        std::stringstream sStream;
        sStream << text;
        std::map<std::string, Entry> tempIndex;
        while (sStream >> word) {
            auto it = tempIndex.find(word);
            if (it == tempIndex.end()) {
                tempIndex.insert(std::pair<std::string, Entry>(word, Entry(currentId, 1)));
            } else {
                it->second.count++;
            }
        }
        if (!tempIndex.empty()) {
            std::string currentWord;
            mutex.lock();
            for (auto it = tempIndex.begin(); it != tempIndex.end(); it++) {
                auto it2 = _freq_dictionary.find(it->first);
                if (it2 != _freq_dictionary.end()) {
                    it2->second.push_back(it->second);
                } else {
                    std::vector<Entry> tempEntry;
                    tempEntry.push_back(it->second);
                    _freq_dictionary.insert(std::pair<std::string, std::vector<Entry>>(it->first, tempEntry));
                }
            }
            mutex.unlock();
        }
    };

    const size_t DOCS_SIZE = input_docs.size();
    std::vector<std::thread> threadIndex;
    size_t docId = 0;
    unsigned int threadCount = std::thread::hardware_concurrency();
    if (threadCount <= 0) {
        threadCount = MIN_THREAD_COUNT;
    }
    for (int threadNum = 0; threadNum < threadCount && threadNum < DOCS_SIZE; threadNum++) {
        threadIndex.push_back(std::thread(task, std::ref(docId), std::ref(freq_dictionary), std::ref(docs)));
    }
    for (int threadNum = 0; threadNum < threadIndex.size(); threadNum++) {
        threadIndex[threadNum].join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    auto it = freq_dictionary.find(word);
    if (it != freq_dictionary.end()){
        return it->second;
    } else {
        return std::vector<Entry>();
    }
}