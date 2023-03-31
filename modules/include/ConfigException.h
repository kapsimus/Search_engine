#pragma once
#include <exception>
#include <string>

class ConfigException: public std::exception {
private:
    std::string message;
public:
    ConfigException(std::string msg);
    std::string getMessage() const;
};