#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileDownloader.h"
#include "TranslationTTSWidget.h"
#include "QTimer"
#include "QKeyEvent"
#include "QLabel"
#include "Stats.h"
#include "QSet"
#include "versioncontroller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileD = new FileDownloader();
    tts = new TranslationTTSWidget(this);
    wordsStats = new Stats(fileD);
    verC = new VersionController(this);

    connect(wordsStats,&Stats::setUpComplite,this,&MainWindow::onComplideDownload);
    connect(fileD,&FileDownloader::processComplite,wordsStats,&Stats::setUpWords);    

    connect(verC,&VersionController::processComplite,this,[&](){
        QString displayVer {"VER (" + verC->getAppVer() + ")\t TEXT-LIST-VER (" + verC->getDicVer() + ")"};
        ui->statusbar->showMessage(displayVer);
    });

    answeredWords = 0;

    ui->statusbar->setStyleSheet("QStatusBar{color: rgba(255, 85, 0, 150);}");

    correctChar = ("QLabel { border-width: 1px; border-style: solid; border-radius: 4px;background-color: rgb(170, 255, 127);}");
    wrongChar   = ("QLabel { border-width: 1px; border-style: solid; border-radius: 4px;background-color: rgba(255, 0, 0,200);}");
    emptyChar   = ("QLabel { border-width: 1px; border-style: solid; border-radius: 4px;background-color: rgb(245, 166, 35);}");
}

void MainWindow::checkAnswer() {
    if(!itBegin.value()->en.isEmpty() && inputStr == itBegin.value()->en) {
        tts->playTranslation(itBegin.value()->en);

        ++answeredWords;

        ui->progressBar->setValue(((float(answeredWords) / float(totalWords)) * 100.f));
        ui->progressBar->setFormat(QString::number(answeredWords) + '/' + QString::number(totalWords));

        itBegin.value()->answerRatio += 1;

        qDebug() << itBegin.value()->answerRatio;

        setNewWord(++itBegin,itEnd);
    }
    else if(!itBegin.value()->en.isEmpty()) {
        tts->playTranslation(itBegin.value()->en);
        ui->label_2->setText(itBegin.value()->en);

        itBegin.value()->answerRatio -= 1;

        qDebug() << itBegin.value()->answerRatio;

        QTimer::singleShot(1000,[this](){
            ui->label_2->clear();
        });
    }
}

void MainWindow::onComplideDownload() {

    totalWords = wordsStats->getCount();

    ui->progressBar->setMaximum(totalWords);
    ui->progressBar->setValue(0);
    ui->progressBar->setFormat(QString::number(answeredWords) + '/' + QString::number(totalWords));

    labelWords.fill(nullptr,wordsStats->getMaxLength());

    QFont font;
    font.setPixelSize(25);

    for(int i = 0; i < labelWords.size();++i){
        QLabel * temp = new QLabel(ui->widget);
        labelWords[i] = temp;
        ui->horizontalLayout->addWidget(temp);
        temp->setStyleSheet(emptyChar);
        temp->setAlignment(Qt::AlignmentFlag::AlignCenter);
        temp->setFont(font);

        temp->hide();
    }

    itBegin = wordsStats->getWordsQueBegin();
    itEnd = wordsStats->getWordsQueEnd();

    setNewWord(itBegin,itEnd);
}

void MainWindow::setNewWord(QMap<int,WordInfo*>::Iterator itBegin,QMap<int,WordInfo*>::Iterator itEnd) {

    if(itBegin == itEnd){
        this->close();
    }

    ui->label->clear();
    ui->label_2->clear();
    inputStr.clear();

    ui->label->setText(itBegin.value()->ru);

    for(int i = 0; i < labelWords.size() && i < itBegin.value()->en.size() ;++i){
        if(!labelWords[i]->isVisible()){
            labelWords[i]->show();
        }
        labelWords[i]->clear();
    }

    for(int i = itBegin.value()->en.size(); i < labelWords.size();++i){
        if(labelWords[i]->isVisible()){
            labelWords[i]->hide();
        }
    }
}

void MainWindow::dispaleWord() {

    for(int i = itBegin.value()->en.size() - 1; inputStr.size() - 1 < i; --i){
        labelWords[i]->clear();
        labelWords[i]->setStyleSheet(emptyChar);
    }

    for(int i = 0;i < itBegin.value()->en.size() && i < inputStr.size() ;++i){
        labelWords[i]->setText(inputStr[i]);

        if(itBegin.value()->en[i] == inputStr[i]) {
            labelWords[i]->setStyleSheet(correctChar);
        }
        else{
            labelWords[i]->setStyleSheet(wrongChar);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    if(event->key() == Qt::Key_Backspace ) {
        inputStr.chop(1);
        qDebug() << "Key_Backspace";
    } else if(event->key() == Qt::Key_Return){
        checkAnswer();
    }

    if(inputStr.size() < itBegin.value()->en.size() ) {

        switch(event->key()) {
        case Qt::Key_Q:
            qDebug() << "Key_Q";
            inputStr += "q";
            break;
        case Qt::Key_W:
            qDebug() << "Key_W";
            inputStr += "w";
            break;
        case Qt::Key_E:
            qDebug() << "Key_E";
            inputStr += "e";
            break;
        case Qt::Key_R:
            qDebug() << "Key_R";
            inputStr += "r";
            break;
        case Qt::Key_T:
            qDebug() << "Key_T";
            inputStr += "t";
            break;
        case Qt::Key_Y:
            qDebug() << "Key_Y";
            inputStr += "y";
            break;
        case Qt::Key_U:
            qDebug() << "Key_U";
            inputStr += "u";
            break;
        case Qt::Key_I:
            qDebug() << "Key_I";
            inputStr += "i";
            break;
        case Qt::Key_O:
            qDebug() << "Key_O";
            inputStr += "o";
            break;
        case Qt::Key_P:
            qDebug() << "Key_P";
            inputStr += "p";
            break;
        case Qt::Key_A:
            qDebug() << "Key_A";
            inputStr += "a";
            break;
        case Qt::Key_S:
            qDebug() << "Key_S";
            inputStr += "s";
            break;
        case Qt::Key_D:
            qDebug() << "Key_D";
            inputStr += "d";
            break;
        case Qt::Key_F:
            qDebug() << "Key_F";
            inputStr += "f";
            break;
        case Qt::Key_G:
            qDebug() << "Key_G";
            inputStr += "g";
            break;
        case Qt::Key_H:
            qDebug() << "Key_H";
            inputStr += "h";
            break;
        case Qt::Key_J:
            qDebug() << "Key_J";
            inputStr += "j";
            break;
        case Qt::Key_K:
            qDebug() << "Key_K";
            inputStr += "k";
            break;
        case Qt::Key_L:
            qDebug() << "Key_L";
            inputStr += "l";
            break;
        case Qt::Key_Z:
            qDebug() << "Key_Z";
            inputStr += "z";
            break;
        case Qt::Key_X:
            qDebug() << "Key_X";
            inputStr += "x";
            break;
        case Qt::Key_C:
            qDebug() << "Key_C";
            inputStr += "c";
            break;
        case Qt::Key_V:
            qDebug() << "Key_V";
            inputStr += "v";
            break;
        case Qt::Key_B:
            qDebug() << "Key_B";
            inputStr += "b";
            break;
        case Qt::Key_N:
            qDebug() << "Key_N";
            inputStr += "n";
            break;
        case Qt::Key_M:
            qDebug() << "Key_M";
            inputStr += "m";
            break;
        case Qt::Key_Apostrophe:
            qDebug() << "Key_Apostrophe";
            inputStr += "'";
            break;
        case Qt::Key_Space:
            qDebug() << "Key_Space";
            inputStr += " ";
            break;
        default:
            QWidget::keyPressEvent(event);
            break;
        }
    }
    dispaleWord();
}

MainWindow::~MainWindow() {
    wordsStats->saveStatsToJson();
    verC->saveJson();

    delete ui;
    delete fileD;
}