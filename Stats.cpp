#include "Stats.h"

Stats::Stats(FileDownloader *sourceIn) {
    source = sourceIn;
    maxLength = 0;
}

void Stats::saveStatsToJson() {
    QFile output ("stats.json");
    QJsonObject obj;

    for(auto & curPair : allWords) {
        QJsonObject objData;
        objData["ru"] = curPair.ru;
        objData["ratio"] = curPair.answerRatio;

        obj[curPair.en] = objData;
    }

    QJsonDocument doc(obj);

    if(output.open(QFile::WriteOnly)) {
        QByteArray jsonData = doc.toJson(QJsonDocument::Indented);

        output.write(jsonData);

        output.close();
    }
}

void Stats::setStatsFromJson() {
    QFile input("stats.json");

    if(input.open(QFile::ReadOnly)){
        QByteArray  jsonData = input.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);

        QJsonObject obj = doc.object();

        for(auto iter = obj.begin(); iter != obj.end();++iter) {

            const QJsonObject & value = iter.value().toObject();

            WordInfo temp;

            for(auto iterValue = value.begin(); iterValue != value.end();++iterValue) {
                if(iterValue->isDouble()) {
                    temp.answerRatio = iterValue->toInt();
                }
                else if(iterValue->isString()) {
                    temp.ru = iterValue.value().toString();
                }
            }

            temp.en = iter.key();

            if(maxLength < iter.key().length()){
                maxLength = iter.key().length();
            }

            allWords.insert(iter.key(),temp);
        }

        input.close();
    }
}

void Stats::setUpWords(bool net) {
    setStatsFromJson();

    if(net) {
        auto vec = source->getEnVector();
        for(int i = 0 ;i < vec.size();++i ) {
            if(!allWords.count(vec[i])) {
                WordInfo temp {0,source->getRu(i),vec[i]};
                allWords.insert(vec[i],temp);

                if(maxLength < vec[i].length()){
                    maxLength = vec[i].length();
                }
            }
        }
    }

    for(auto iter = allWords.begin(); iter != allWords.end(); ++iter) {
        int tempRatio = iter.value().answerRatio;

        do {
            ++tempRatio;
        }while(wordsMap.count(tempRatio) != 0);

        wordsMap.insert(tempRatio,&iter.value());
    }

    emit setUpComplite();
}

QMap<int,WordInfo*>::Iterator Stats::getWordsQueBegin() {
    return wordsMap.begin();
}
QMap<int,WordInfo*>::Iterator Stats::getWordsQueEnd() {
    return wordsMap.end();
}

int Stats::getCount() {
    return wordsMap.count();
}
int Stats::getMaxLength() {
    return maxLength;
}