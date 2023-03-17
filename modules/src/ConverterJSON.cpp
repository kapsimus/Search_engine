#include <fstream>
#include <iostream>
#include "ConverterJSON.h"

void ConverterJSON::SetFilesFolderPath(const std::string &path)
{
    if (!path.empty()) {
        FILES_FOLDER_PATH = path;
    }

}

void ConverterJSON::SetConfigPath(const std::string &path) {
    if (!path.empty()) {
        CONFIG_PATH = path;
    }
}
void ConverterJSON::SetRequestsPath(const std::string &path) {
    if (!path.empty()) {
        REQUESTS_PATH = path;
    }
}
void ConverterJSON::SetAnswersPath(const std::string &path) {
    if (!path.empty()) {
        ANSWERS_PATH = path;
    }
}

std::string ConverterJSON::GetFilesFolderPath() const
{
    return FILES_FOLDER_PATH;
}

std::string ConverterJSON::GetConfigPath() const {
    return CONFIG_PATH;
}
std::string ConverterJSON::GetRequestsPath() const {
    return REQUESTS_PATH;
}
std::string ConverterJSON::GetAnswersPath() const {
    return ANSWERS_PATH;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> requests;
    std::ifstream file(GetRequestsPath());
    if (!file.is_open()) {
        std::cout << "Unable to open file " << GetRequestsPath() << std::endl;
        return requests;
    }
    nlohmann::json data = nlohmann::json::parse(file);
    file.close();
    for (auto it = data["requests"].begin(); it != data["requests"].end(); it++) {
        requests.push_back(*it);
    }
    requestCount = requests.size();
    return requests;
}

bool ConverterJSON::SetRequests(const std::vector<std::string>& requestList) {
    if (!requestList.empty()) {
        std::ofstream file(GetRequestsPath());
        if (!file.is_open()) {
            std::cout << "Unable to open file " << GetRequestsPath() << std::endl;
            return false;
        }
        nlohmann::json json;
        for (auto request: requestList){
            json["requests"] += request;
        }
        file << json.dump(4);
        file.close();
        return true;
    } else {
        return false;
    }
}

bool ConverterJSON::WriteDocsToFiles(const std::vector<std::string> &documentsList) {
    nlohmann::json config = this->GetConfig();
    if (config.empty()) {
        return false;
    }
    config["files"].clear();
    std::string prefix{"./resources/filename"};
    int fileNumber = 1;
    if (!documentsList.empty()) {
        std::string suffix;
        std::string filename;
        for (auto doc: documentsList) {
            suffix = std::to_string(fileNumber) + ".txt";
            if (fileNumber > 999) {
                filename = prefix + suffix;
            } else if (fileNumber > 99) {

                filename = prefix + "0" + suffix;
            } else if (fileNumber > 9) {
                filename = prefix + "00" + suffix;
            } else  {
                filename = prefix + "000" + suffix;
            }
            config["files"] += filename;
            ++fileNumber;
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cout << "Unable to open file " << filename << std::endl;
                return false;
            }
            file << doc;
            file.close();
        }
        std::ofstream fileConfig(GetConfigPath());
        if (!fileConfig.is_open()) {
            std::cout << "Unable to open file " << GetConfigPath() << std::endl;
            return false;
        }
        fileConfig << config.dump(4);
        fileConfig.close();
    }
    return true;
}

bool ConverterJSON::WriteFilesToConfig(const std::vector<std::string> &documentsList) {
    nlohmann::json config = this->GetConfig();
    if (config.empty()) {
        return false;
    }
    config["files"].clear();
    if (!documentsList.empty()) {
        for (auto doc: documentsList) {
            config["files"] += doc;
        }
        std::ofstream fileConfig(GetConfigPath());
        if (!fileConfig.is_open()) {
            std::cout << "Unable to open file " << GetConfigPath() << std::endl;
            return false;
        }
        fileConfig << config.dump(4);
        fileConfig.close();
    }
    return true;
}

nlohmann::json ConverterJSON::GetConfig() {
    std::ifstream file(GetConfigPath());
    nlohmann::json config;
    if (!file.is_open()) {
        std::cout << "Unable to open file " << GetConfigPath() << std::endl;
        return config;
    }
    config = nlohmann::json::parse(file);
    file.close();
    return config;
}

int ConverterJSON::GetResponsesLimit() {
    std::ifstream file(GetConfigPath());
    if (!file.is_open()) {
        std::cout << "Unable to open file " << GetConfigPath() << std::endl;
        return -1;
    }
    nlohmann::json data = nlohmann::json::parse(file);
    file.close();
    return data["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> files;
    std::ifstream file(GetConfigPath());
    if (!file.is_open()) {
        std::cout << "Unable to open file " << GetConfigPath() << std::endl;
        return files;
    }
    nlohmann::json data = nlohmann::json::parse(file);
    file.close();
    for (auto it = data["files"].begin(); it != data["files"].end(); it++) {
        files.push_back(*it);
    }
    return files;
}

void ConverterJSON::NormalizeDocuments() {
    auto docList = this->GetTextDocuments();
    if (!docList.empty()) {
        for (int i = 0; i < docList.size(); ++i) {
            std::ifstream file(docList[i]);
            if (file.is_open()) {
                std::string in, out;
                auto ss = std::ostringstream{};
                ss << file.rdbuf();
                in = ss.str();
                file.close();
                for (auto symbol: in) {
                    if (symbol > 96 && symbol < 123) {
                        out += symbol;
                    } else if (symbol > 64 && symbol < 91) {
                        out += (symbol + 32);
                    } else if (symbol == ' ') {
                        out += symbol;
                    } else if (symbol == '-') {
                        out += symbol;
                    } else if (symbol == '\'') {
                        out += symbol;
                    }else if (symbol > 47 && symbol < 58) {
                        out += symbol;
                    }
                }
                std::ofstream fileOut(docList[i]);
                if (fileOut.is_open()) {
                    fileOut << out;
                    fileOut.close();
                } else {
                    std::cout << "Unable to open file " << docList[i] << std::endl;
                }
            } else {
                std::cout << "Unable to open file " << docList[i] << std::endl;
            }
        }
    } else return;

}

std::string ConverterJSON::NormalizeDocument(std::string &text)
{
    std::string out;
    for (auto symbol: text) {
        if (symbol > 96 && symbol < 123) {
            out += symbol;
        } else if (symbol > 64 && symbol < 91) {
            out += (symbol + 32);
        } else if (symbol == ' ') {
            out += symbol;
        } else if (symbol == '-') {
            out += symbol;
        } else if (symbol == '\'') {
            out += symbol;
        }else if (symbol > 47 && symbol < 58) {
            out += symbol;
        }
    }
    return out;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> &answers) {
    std::ofstream file(GetAnswersPath());
    if (answers.empty()) {
        file.close();
        return;
    } else {
        nlohmann::json json;
        std::string requestName;
        size_t requestNumber;
        for (int i = 0; i < answers.size(); ++i) {
            requestNumber = i + 1;
            if (requestNumber < 10) requestName = "request00";
            else if (requestNumber < 100) requestName = "request0";
            else requestName = "request";
            requestName += std::to_string(requestNumber);
            if (answers[i].empty()) {
                json["answers"][requestName]["result"] = "false";
            } else {
                json["answers"][requestName]["result"] = "true";
                for (int j = 0; j < answers[i].size(); ++j) {
                    json["answers"][requestName]["relevance"] += {{"docid", answers[i][j].doc_id}, {"rank", answers[i][j].rank}};
                }
            }
        }
        file << json.dump(4);
        file.close();
    }
}
