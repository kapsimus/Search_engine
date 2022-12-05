#include <map>
#include <sstream>
#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<Entry>> wordsCount;
    std::vector<std::vector<RelativeIndex>> out;
    if (queries_input.empty()) {
        return out;
    }
    for (std::string request: queries_input) {
        std::stringstream sStream;
        sStream << request;
        std::vector<std::string> words;
        std::string word;
        while (sStream >> word) {
            if (words.empty()) {
                words.push_back(word);
            } else {
                bool unique = true;
                for (std::string uniqueWord: words){
                    if (word == uniqueWord) {
                        unique = false;
                        break;
                    }
                }
                if (unique) {
                    words.push_back(word);
                }
            }
        }
        //заполнение вспомогательного вектора частоты слов
        std::vector<int> frequency;
        for (int i = 0; i < words.size(); i++) {
            wordsCount.push_back(_index.GetWordCount(words[i]));
            int count = 0;
            for (int j = 0; j < wordsCount[i].size(); j++) {
                count += wordsCount[i][j].count;
            }
            frequency.push_back(count);
        }
        //сортировка
        int size = frequency.size();
        for (int i = 0; i < size; i++) {
            int minIndex = i;
            int minCount = frequency[i];
            for (int j = i + 1; j < size; j++) {
                if (frequency[j] < minCount) {
                    minCount = frequency[j];
                    minIndex = j;
                }
            }
            std::swap(frequency[i], frequency[minIndex]);
            std::swap(wordsCount[i], wordsCount[minIndex]);
        }
        //заполнение вектора найденных документов
        std::vector<std::vector<int>> docsId(size);
        for (int i = 0; i < size; i++) {
            if (i == 0) {
                for (int j = 0; j < wordsCount[i].size(); j++) {
                    docsId[i].push_back(wordsCount[i][j].doc_id);
                }
            } else {
                for (int j = 0; j < wordsCount[i].size(); j++) {
                    for (int k = 0; k < docsId[i-1].size(); k++){
                        if (docsId[i-1].empty()) {
                            break;
                        }
                        if (wordsCount[i][j].doc_id == docsId[i-1][k]) {
                            docsId[i].push_back(wordsCount[i][j].doc_id);
                            break;
                        }
                    }
                }
            }
        }
    }

    return out;
}