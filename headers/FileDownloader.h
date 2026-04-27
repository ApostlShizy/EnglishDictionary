#pragma once
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QUrl>

class FileDownloader : public QObject {
    Q_OBJECT

signals:
    void processComplite(bool net);

public:
    FileDownloader();

    int getCount() const;
    QString getRu(int index) const;
    QString getEng(int index) const;
    const QVector<QString> & getEnVector() const;

    void download(const QString &urlStr);

private slots:
    void onFinished(QNetworkReply *reply);
    void processText(const QByteArray &data);

private:
    QNetworkAccessManager manager;
    QVector<QString> ruWords;
    QVector<QString> engWords;
};