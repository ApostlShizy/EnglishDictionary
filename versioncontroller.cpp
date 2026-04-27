#include "versioncontroller.h"

VersionController::VersionController(QObject *parent)
    : QObject{parent}
{

    changed = false;

    connect(&manager, &QNetworkAccessManager::finished, this, &VersionController::onFinished);
    download("https://raw.githubusercontent.com/ApostlShizy/EngWords/refs/heads/main/version.json");

    QFile input("version.json");

    if(input.open(QFile::ReadOnly)){
        QByteArray  jsonData = input.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);

        if (doc.isObject()) {
            QJsonObject obj = doc.object();

            appVerF = obj.find("appVersion").value().toString();
            dicVerF = obj.find("dictVersion").value().toString();

            qDebug () << "From file" << appVerF;
            qDebug () << "From file" << dicVerF;
        }
    }

    input.close();
}

void VersionController::download(const QString &urlStr) {
    QUrl url(urlStr);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "QtDownloader");
    manager.get(request);
}

void VersionController::onFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QString fileName = reply->url().fileName();

    if (fileName.endsWith(".json")) {
        processJson(data);
    }

    emit processComplite();

    reply->deleteLater();
}

// .json processing
void VersionController::processJson(const QByteArray &data) {

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        return;
    }

    if (doc.isObject()) {
        QJsonObject obj = doc.object();


        appVerD = obj.find("appVersion").value().toString();
        dicVerD = obj.find("dictVersion").value().toString();

        qDebug () << "From download" << appVerD;
        qDebug () << "From download" << dicVerD;

        changed = true;

        if(appVerD != appVerF) {
            offerDownload();
        }
    }
}

void VersionController::saveJson() {
    if(changed) {
        QFile output("version.json");
        if(output.open(QFile::WriteOnly)){
            QJsonObject obj;
            obj["appVersion"] = appVerF;
            obj["dictVersion"] = dicVerD;

            QJsonDocument doc(obj);

            QByteArray data = doc.toJson(QJsonDocument::Indented);

            output.write(data);

            output.close();
        }
    }
}

void VersionController::offerDownload() {
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr,"","Версия приложения устарела. Хотите скачать новую ?", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        QString link = "https://github.com/ApostlShizy/EnglishDictionary/releases";
        QDesktopServices::openUrl(QUrl(link));
    }
}

const QString VersionController::getAppVer() {
    return appVerF;
}
const QString VersionController::getDicVer() {
    if(dicVerD.isEmpty()) {
        return dicVerF;
    }
    return dicVerD;
}