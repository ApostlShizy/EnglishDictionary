#pragma once

#include <QMainWindow>
#include "QMap"

class FileDownloader;
class TranslationTTSWidget;
class QKeyEvent;
class QLabel;
class Stats;
class VersionController;

struct WordInfo;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void setNewWord(QMap<int,WordInfo*>::Iterator itBegin,QMap<int,WordInfo*>::Iterator itEnd);
    void dispaleWord();

    Ui::MainWindow *ui;
    FileDownloader * fileD;
    TranslationTTSWidget * tts;
    Stats * wordsStats;

    int totalWords;
    int answeredWords;

    QVector<QLabel*> labelWords;

    QString inputStr;

    QString wrongChar;
    QString correctChar;
    QString emptyChar;

    QMap<int,WordInfo*>::Iterator itBegin;
    QMap<int,WordInfo*>::Iterator itEnd;

    VersionController * verC;

private slots:
    void checkAnswer();
    void onComplideDownload();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

