#include "FileDownloader.h"

FileDownloader::FileDownloader() {
    connect(&manager, &QNetworkAccessManager::finished, this, &FileDownloader::onFinished);
    download("https://raw.githubusercontent.com/ApostlShizy/EngWords/refs/heads/main/EngWords.txt");
}

//from emplace url download file
void FileDownloader::download(const QString &urlStr) {
    QUrl url(urlStr);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "QtDownloader");
    manager.get(request);
}

//process what type of file downloadet
void FileDownloader::onFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Ошибка скачивания:" << reply->errorString();
        reply->deleteLater();
        emit processComplite(false);

        return;
    }

    QByteArray data = reply->readAll();
    QString fileName = reply->url().fileName();

    if (fileName.endsWith(".txt")) {
        processText(data);
    }
    else {
        qDebug() << "Получены данные неизвестного формата";
        emit processComplite(false);
    }

    reply->deleteLater();
}

//.txt processing
void FileDownloader::processText(const QByteArray &data) {
    QString text = QString::fromUtf8(data);

    QTextStream in(&text);

    QRegularExpression regEx (R"(^\s*([A-Za-z\']+\s[A-Za-z\']*)\s*-\s*([\p{Cyrillic} ,\(\)]+)$)");

    for(QString line = in.readLine(); !line.isNull();line = in.readLine()) {
        QRegularExpressionMatch match = regEx.match(line);

        QString english = match.captured(1);
        QString russian = match.captured(2);

        ruWords.append(russian);
        engWords.append(english.trimmed());
    }

    emit processComplite(true);
}

//get ru word from index
QString FileDownloader::getRu(int index) const {
    return ruWords[index];
}
//get eng word from index
QString FileDownloader::getEng(int index) const {
    return engWords[index];
}

//get ref on QVector with en words
const QVector<QString> &FileDownloader::getEnVector() const {
    return engWords;
}
//count of words in vector
int FileDownloader::getCount() const {
    return engWords.size();
}

