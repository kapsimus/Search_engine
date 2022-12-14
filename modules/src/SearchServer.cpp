#include <map>
#include <sstream>
#include <algorithm>
#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<RelativeIndex>> out;
    if (queries_input.empty()) {
        return out;
    }
    for (std::string request: queries_input) {
        std::vector<std::vector<Entry>> wordsList;
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
            wordsList.push_back(_index.GetWordCount(words[i]));
            int count = 0;
            for (int j = 0; j < wordsList[i].size(); j++) {
                count += wordsList[i][j].count;
            }
            frequency.push_back(count);
        }
        //сортировка
        int wordsCount = frequency.size();
        for (int i = 0; i < wordsCount; i++) {
            int minIndex = i;
            int minCount = frequency[i];
            for (int j = i + 1; j < wordsCount; j++) {
                if (frequency[j] < minCount) {
                    minCount = frequency[j];
                    minIndex = j;
                }
            }
            std::swap(frequency[i], frequency[minIndex]);
            std::swap(wordsList[i], wordsList[minIndex]);
        }
        //заполнение вектора найденных документов
        std::vector<std::vector<size_t>> docsId;
        for (int i = 0; i < wordsCount; i++) {
            std::vector<size_t> docsIdArray;
            docsId.push_back(docsIdArray);
            if (i == 0) {
                if (!wordsList[i].empty()) {
                    for (int j = 0; j < wordsList[i].size(); j++) {
                        docsId[i].push_back(wordsList[i][j].doc_id);
                    }
                }
            } else {
                for (int j = 0; j < wordsList[i].size(); j++) {

                    for (int k = 0; k < docsId[i-1].size(); k++){
                        if (docsId[i-1].empty()) {
                            break;
                        }
                        if (wordsList[i][j].doc_id == docsId[i - 1][k]) {
                            docsId[i].push_back(wordsList[i][j].doc_id);
                            break;
                        }
                    }
                }
            }
        }
        //заполняем вектор релевантности
        std::vector<RelativeIndex> relIndexes;
        if (docsId.back().empty()) {
            out.push_back(relIndexes);
        } else {
            //docsId.back() - список id документов на последней итерации поиска.
            std::vector<size_t> foundDocsId = docsId.back();
            std::map<size_t, std::vector<int>> absIndexesTable;
            int maxAbsRel = 0;
            for (size_t docID: foundDocsId) {
                std::vector<int> wordsCountInDoc(frequency.size());
                std::vector<Entry> entryList;
                int currentAbsRel = 0;
                for (int i = 0; i < words.size(); i++) {
                    entryList = _index.GetWordCount(words[i]);
                    for (Entry entry: entryList) {
                        if (entry.doc_id == docID) {
                            wordsCountInDoc[i] += entry.count;
                            currentAbsRel += entry.count;
                        }
                    }
                }
                if (currentAbsRel > maxAbsRel) {
                    maxAbsRel = currentAbsRel;
                }
                absIndexesTable.insert(std::pair<size_t, std::vector<int>>(docID, wordsCountInDoc));
            }
            for (auto currentDoc: absIndexesTable) {
                RelativeIndex relIndex;
                relIndex.doc_id = currentDoc.first;
                int currentAbsRel = 0;
                for (auto wordsCount: currentDoc.second) {
                    currentAbsRel += wordsCount;
                }
                relIndex.rank = (float)currentAbsRel / maxAbsRel;
                relIndexes.push_back(relIndex);
            }
            out.push_back(relIndexes);
        }
    }
    //сортировка в порядке возрастания относительных индексов
    if (!out.empty()) {
        for (auto& indexes: out) {
            std::sort(indexes.begin(), indexes.end(), [](RelativeIndex a, RelativeIndex b) {
                return a.rank > b.rank;
            });
        }
    }
    return out;
}