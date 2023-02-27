#include "settings.h"
#include "nlohmann/json.hpp"
#include "../modules/include/ConverterJSON.h"
#include <QString>
#include <string>

const QString &Settings::configPath() const
{
    return _configPath;
}

void Settings::setConfigPath(const QString &newConfigPath)
{
    _configPath = newConfigPath;
}

const QString &Settings::requestPath() const
{
    return _requestPath;
}

void Settings::setRequestPath(const QString &newRequestPath)
{
    _requestPath = newRequestPath;
}

const QString &Settings::ansverPath() const
{
    return _ansverPath;
}

void Settings::setAnsverPath(const QString &newAnsverPath)
{
    _ansverPath = newAnsverPath;
}

const QString &Settings::filesFolderPath() const
{
    return _filesFolderPath;
}

void Settings::setFilesFolderPath(const QString &newFilesFolderPath)
{
    _filesFolderPath = newFilesFolderPath;
}

const QString &Settings::name() const
{
    return _name;
}

void Settings::setName(const QString &newName)
{
    _name = newName;
}

const QString &Settings::version() const
{
    return _version;
}

void Settings::setVersion(const QString &newVersion)
{
    _version = newVersion;
}

int Settings::maxResponses() const
{
    return _maxResponses;
}

void Settings::setMaxResponses(int newMaxResponses)
{
    _maxResponses = newMaxResponses;
}

const QDateTime &Settings::indexUpdateTime() const
{
    return _indexUpdateTime;
}

void Settings::setIndexUpdateTime(const QDateTime &newIndexUpdateTime)
{
    _indexUpdateTime = newIndexUpdateTime;
}

const QTime &Settings::indexUpdateInterval() const
{
    return _indexUpdateInterval;
}

void Settings::setIndexUpdateInterval(const QTime &newIndexUpdateInterval)
{
    _indexUpdateInterval = newIndexUpdateInterval;
}

bool Settings::saveSettings()
{
    return true;
}

bool Settings::loadSettings()
{
    ConverterJSON conv;
    nlohmann::json config = conv.GetConfig();
    if (config.empty()) {
        return false;
    }
    setName(QString::fromStdString(config["config"]["name"]));
    setVersion(QString::fromStdString(config["config"]["version"]));
    setMaxResponses(config["config"]["max_responses"]);
    return true;
}

Settings::Settings()
{

}
