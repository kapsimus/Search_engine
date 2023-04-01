#include "ConfigException.h"

ConfigException::ConfigException(std::string message): _message(message) {}

std::string ConfigException::getMessage() const {
    return _message;
}