#include "TranslationTTSWidget.h"

TranslationTTSWidget::TranslationTTSWidget(QWidget *parent) : QWidget(parent) {
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
}

void TranslationTTSWidget::playTranslation(QString currentText) {
    QUrl url("https://translate.google.com/translate_tts");
    QUrlQuery query;
    query.addQueryItem("ie", "UTF-8");
    query.addQueryItem("q", currentText);
    query.addQueryItem("tl", "en");
    query.addQueryItem("client", "tw-ob");
    url.setQuery(query);

    player->setSource(url);
    player->play();
}
