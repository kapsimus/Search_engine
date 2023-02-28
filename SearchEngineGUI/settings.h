#ifndef SETTINGS_H
#define SETTINGS_H

#pragma once
#include <QString>
#include <QDateTime>

class Settings
{
    QString _configPath;
    QString _requestPath;
    QString _ansverPath;
    QString _filesFolderPath;
    QString _name;
    QString _version;
    int _maxResponses;
    QDateTime _indexUpdateTime;
    QTime _indexUpdateInterval;

public:
    Settings();
    const QString &configPath() const;
    void setConfigPath(const QString &newConfigPath);
    const QString &requestPath() const;
    void setRequestPath(const QString &newRequestPath);
    const QString &ansverPath() const;
    void setAnsverPath(const QString &newAnsverPath);
    const QString &filesFolderPath() const;
    void setFilesFolderPath(const QString &newFilesFolderPath);
    const QString &name() const;
    void setName(const QString &newName);
    const QString &version() const;
    void setVersion(const QString &newVersion);
    int maxResponses() const;
    void setMaxResponses(int newMaxResponses);
    const QDateTime &indexUpdateTime() const;
    void setIndexUpdateTime(const QDateTime &newIndexUpdateTime);
    const QTime &indexUpdateInterval() const;
    void setIndexUpdateInterval(const QTime &newIndexUpdateInterval);

    bool saveSettings();
    bool loadSettings();

};

#endif // SETTINGS_H
