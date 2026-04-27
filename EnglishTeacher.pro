QT += widgets network multimedia

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src\FileDownloader.cpp \
    src\Stats.cpp \
    src\TranslationTTSWidget.cpp \
    src\main.cpp \
    src\mainwindow.cpp \
    src\versioncontroller.cpp \
    src\wordinfo.cpp

HEADERS += \
    headers\FileDownloader.h \
    headers\Stats.h \
    headers\TranslationTTSWidget.h \
    headers\mainwindow.h \
    headers\versioncontroller.h \
    headers\wordinfo.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
