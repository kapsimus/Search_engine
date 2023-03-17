#include <QString>
#include <QFile>
#include <QDir>
#include "settings.h"
#include "nlohmann/json.hpp"

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

const QString &Settings::answerPath() const
{
    return _answerPath;
}

void Settings::setAnswerPath(const QString &newAnswerPath)
{
    _answerPath = newAnswerPath;
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

ConverterJSON &Settings::converter()
{
    return _converter;
}

InvertedIndex &Settings::index()
{
    return _index;
}

SearchServer &Settings::server()
{
    return _server;
}

Settings::Settings():_server(_index)
{
    QFile file("settings.json");
    if (!file.exists()) {
        nlohmann::json json;
        json["paths"]["files"] = QDir::current().absolutePath().toStdString() + "/" + "resources";
        json["paths"]["config"] = QDir::current().absolutePath().toStdString() + "/" + _converter.GetConfigPath();
        json["paths"]["requests"] = QDir::current().absolutePath().toStdString() + "/" + _converter.GetRequestsPath();
        json["paths"]["answers"] = QDir::current().absolutePath().toStdString() + "/" + _converter.GetAnswersPath();
        setConfigPath(QString::fromStdString(json["paths"]["config"]));
        setRequestPath(QString::fromStdString(json["paths"]["requests"]));
        setAnswerPath(QString::fromStdString(json["paths"]["answers"]));
        setFilesFolderPath(QString::fromStdString(json["paths"]["files"]));
        std::string str{json.dump(4)};
        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "Ошибка при открытии файла";
        } else {
            file.write(str.c_str(), str.size());
            file.close();
        }
    } else {
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Ошибка при открытии файла";
        } else {
            QTextStream stream(&file);
            QString text = stream.readAll();
            file.close();
            nlohmann::json json = nlohmann::json::parse(text.toStdString());
            _converter.SetConfigPath(json["paths"]["config"]);
            _converter.SetRequestsPath(json["paths"]["requests"]);
            _converter.SetAnswersPath(json["paths"]["answers"]);
            _converter.SetFilesFolderPath(json["paths"]["files"]);
            setConfigPath(QString::fromStdString(_converter.GetConfigPath()));
            setRequestPath(QString::fromStdString(_converter.GetRequestsPath()));
            setAnswerPath(QString::fromStdString(_converter.GetAnswersPath()));
            setFilesFolderPath(QString::fromStdString(_converter.GetFilesFolderPath()));
        }
    }

}
