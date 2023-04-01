#pragma once
#include <exception>
#include <string>

class ConfigException: public std::exception {
private:
    std::string _message;
public:
    ConfigException(std::string message);
    std::string getMessage() const;
};