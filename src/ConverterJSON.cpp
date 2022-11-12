#include <fstream>
#include <iostream>
#include <sstream>
#include "ConverterJSON.h"


std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> requests;
    std::ifstream file(REQUESTS_PATH);
    if (!file.is_open()) {
        std::cout << "Unable to open file " << REQUESTS_PATH << std::endl;
        return requests;
    }
    nlohmann::json data = nlohmann::json::parse(file);
    file.close();
    for (auto it = data["requests"].begin(); it != data["requests"].end(); it++) {
        requests.push_back(*it);
    }
    return requests;
}

int ConverterJSON::GetResponsesLimit() {
    std::ifstream file(CONFIG_PATH);
    if (!file.is_open()) {
        std::cout << "Unable to open file " << CONFIG_PATH << std::endl;
        return -1;
    }
    nlohmann::json data = nlohmann::json::parse(file);
    file.close();
    return data["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> documents;
    std::vector<std::string> files;
    std::ifstream file(CONFIG_PATH);
    if (!file.is_open()) {
        std::cout << "Unable to open file " << CONFIG_PATH << std::endl;
        return documents;
    }
    nlohmann::json data = nlohmann::json::parse(file);
    file.close();
    for (auto it = data["files"].begin(); it != data["files"].end(); it++) {
        files.push_back(*it);
    }
    if (!files.empty()) {
        for (int i = 0; i < files.size(); ++i) {
            std::ifstream file(files[i]);
            if (file.is_open()) {
                auto ss = std::ostringstream{};
                ss << file.rdbuf();
                documents.push_back(ss.str());
            } else {
                std::cout << "Unable to open file " << files[i] << std::endl;
            }
        }
    }
    return documents;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> &answers) {

}