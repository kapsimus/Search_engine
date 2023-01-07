#pragma once
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include "SearchServer.h"


class ConverterJSON {
private:
    size_t requestCount = 8;
public:
    const std::string CONFIG_PATH = "config.json";
    const std::string REQUESTS_PATH = "requests.json";
    const std::string ANSWERS_PATH = "answers.json";

    ConverterJSON() = default;
/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json (пути к файлам)
*/
    std::vector<std::string> GetTextDocuments();
/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
    int GetResponsesLimit();

/**
* Метод преобразует текст в файлах - переводит все латинские буквы в
* нижний регистр и удаляет все знаки припинания кроме дефисов
*/
    void NormalizeDocuments();
/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
    std::vector<std::string> GetRequests();

/**
* Метод получения данных из файла config.json
* @return возвращает данные файла config.json  в формате nlohmann::json
*/
    nlohmann::json GetConfig();

/**
* Метод записи запросов в файл requests.json
* @return возвращает true в случае успеха и false в случае неудачи
*/
     bool SetRequests(const std::vector<std::string>& requestList);

/**
* Метод записи текстов в файл config.json
* @return возвращает true в случае успеха и false в случае неудачи
*/
    bool WriteDocsToFiles(const std::vector<std::string>& documentsList);

/**
* Положить в файл answers.json результаты поисковых запросов
*/
    void putAnswers(std::vector<std::vector<RelativeIndex>> &answers);
};