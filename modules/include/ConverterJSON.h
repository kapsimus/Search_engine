#pragma once
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include "SearchServer.h"


class ConverterJSON {
private:
    size_t requestCount = 0;
public:
    const std::string CONFIG_PATH = "config.json";
    const std::string REQUESTS_PATH = "requests.json";
    const std::string ANSWERS_PATH = "answers.json";

    ConverterJSON() = default;
/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
    std::vector<std::string> GetTextDocuments();
/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
    int GetResponsesLimit();
/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
    std::vector<std::string> GetRequests();
/**
* Положить в файл answers.json результаты поисковых запросов
*/
    void putAnswers(std::vector<std::vector<RelativeIndex>> &answers);
};