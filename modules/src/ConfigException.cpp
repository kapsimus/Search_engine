#include "ConfigException.h"

ConfigException::ConfigException(std::string msg): message(msg) {}

std::string ConfigException::getMessage() const {
    return message;
}