#pragma once

#ifndef VERSIONCONTROLLER_H
#define VERSIONCONTROLLER_H

// базовые хеддеры
#include <QObject>
#include "QString"
#include "QMessageBox"
#include <QDesktopServices>
#include "QWidget"

// сетевые хеддеры
#include "QUrl"
#include "QNetworkAccessManager"
#include "QBitArray"
#include <QNetworkReply>

// хедеры для работы с файлами (запись-чтение)
#include "QByteArray"
#include "QFile"

// хедеры для работы с json
#include "QJsonDocument"
#include "QJsonObject"

class VersionController : public QObject
{
    Q_OBJECT
public:

    //В конструкторе создать менеджер скачивания, проверить существует ли файл "version.json" на пк, если да извлечь версию и записать в переменные
    explicit VersionController(QObject *parent = nullptr);

    // гетеры для версий
    const QString getAppVer();
    const QString getDicVer();

    // скачивание
    void download(const QString &urlStr);

    // обработка скачанного документа
    void processJson(const QByteArray &data);

    // сохранить изменения
    void saveJson();

public slots:

    // реакция на окончание скачивания
    void onFinished(QNetworkReply *reply);
    // слот с окном который предлагает перейти в репозиторий и скачать актуальную версию
    void offerDownload();

signals:

    // сигнал конца обработки версий
    void processComplite();

private:

    QString appVerD;                // хранение версии программы скачанная
    QString dicVerD;                // хранение версии словаря скачанная

    bool changed;                   // флаг, были ли изменения

    QString appVerF;                // хранение версии программы из файла
    QString dicVerF;                // хранение версии словаря из файла

    QNetworkAccessManager manager;  // менеджер скачивания
};

#endif // VERSIONCONTROLLER_H
