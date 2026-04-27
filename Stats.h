#pragma once

#include "QObject"
#include "QMap"
#include "QString"
#include "QJsonObject"
#include "QJsonDocument"
#include "QFile"
#include "FileDownloader.h"
#include "QBitArray"
#include "QByteArray"
#include "wordinfo.h"

class Stats : public QObject {
    Q_OBJECT

private:    
    QMap<int,WordInfo*> wordsMap;
    QMap<QString,WordInfo> allWords;
    FileDownloader * source;

    int maxLength;

public slots:
    void setUpWords(bool net);

public:
    Stats() = default;    
    Stats(FileDownloader * sourceIn);

    void saveStatsToJson();
    void setStatsFromJson();

    QMap<int,WordInfo*>::Iterator getWordsQueBegin();
    QMap<int,WordInfo*>::Iterator getWordsQueEnd();

    int getCount();
    int getMaxLength();

signals:
    void setUpComplite();
};
