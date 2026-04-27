#pragma once

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QUrlQuery>

class TranslationTTSWidget : public QWidget {
    Q_OBJECT
public:
    TranslationTTSWidget(QWidget *parent = nullptr);

    void playTranslation(QString currentText);

private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};