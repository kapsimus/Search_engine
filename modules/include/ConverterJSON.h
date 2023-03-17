#pragma once
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include "SearchServer.h"


class ConverterJSON {
private:
    size_t requestCount = 8;
    std::string FILES_FOLDER_PATH = "resources";
    std::string CONFIG_PATH = "config.json";
    std::string REQUESTS_PATH = "requests.json";
    std::string ANSWERS_PATH = "answers.json";
public:
/**
* сеттер переменной пути к каталогу с текстовыми файлами
* @path передаётся путь к каталогу с файлами
*/
    void SetFilesFolderPath(const std::string& path);
/**
* сеттер переменной пути к файлу Config
* @path передаётся путь к файлу Config
*/
    void SetConfigPath(const std::string& path);
/**
* сеттер переменной пути к файлу Request
* @path передаётся путь к файлу Request
*/
    void SetRequestsPath(const std::string& path);
/**
* сеттер переменной пути к файлу Answers
* @path передаётся путь к файлу Answers
*/
    void SetAnswersPath(const std::string& path);

/**
* геттер переменной пути к каталогу с текстовыми файлами
* @return возвращается путь каталогу с текстовыми файлами
*/
    std::string GetFilesFolderPath() const;
/**
* геттер переменной пути к файлу Config
* @return возврвщается путь к файлу Config
*/
    std::string GetConfigPath() const;
/**
* геттер переменной пути к файлу Request
* @return возврвщается путь к файлу Request
*/
    std::string GetRequestsPath() const;
/**
* геттер переменной пути к файлу Answers
* @return возврвщается путь к файлу Answers
*/
    std::string GetAnswersPath() const;

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
* @return возвращает максимальное количество ответов
*/
    int GetResponsesLimit();

/**
* Метод преобразует текст в файлах - переводит все латинские буквы в
* нижний регистр и удаляет все знаки припинания кроме дефисов
*/
    void NormalizeDocuments();

/**
* Метод преобразует текст в переданной строке - переводит все латинские буквы в
* нижний регистр и удаляет все знаки припинания кроме дефисов
* @text преобразуемый текст
*/
    std::string NormalizeDocument(std::string &text);

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
* Метод записи текстов в файл config.json (предназначен для теста)
* @return возвращает true в случае успеха и false в случае неудачи
*/
    bool WriteDocsToFiles(const std::vector<std::string>& documentsList);

/**
* Метод записи путей к файлам в файл config.json
* @return возвращает true в случае успеха и false в случае неудачи
*/
    bool WriteFilesToConfig(const std::vector<std::string> &documentsList);

/**
* Положить в файл answers.json результаты поисковых запросов
*/
    void putAnswers(std::vector<std::vector<RelativeIndex>>& answers);
};
