#include <fstream>
#include <iostream>
#include "ConverterJSON.h"


std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> requests;
    std::ifstream file(CONFIG_PATH);
    if (!file.is_open()) {
        std::cout << "Unable to open file " << CONFIG_PATH << std::endl;
        return requests;
    }
    nlohmann::json data = nlohmann::json::parse(file);
    file.close();
    for (auto it = data["files"].begin(); it != data["files"].end(); it++) {
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


    return documents;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {

}