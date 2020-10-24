TEMPLATE = app
TARGET   = wkhtml-gui
INCLUDEPATH += include .
UI_DIR = ui
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION_MAJOR = 0
VERSION_MINOR = 0
VERSION_BUILD = 1
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}

CONFIG += c++11 lrelease embed_translations

DEFINES += \
    QT_DISABLE_DEPRECATED_BEFORE=0x060000 \   # disables all the APIs deprecated before Qt 6.0.0
    "VERSION_MAJOR=$$VERSION_MAJOR" \
    "VERSION_MINOR=$$VERSION_MINOR" \
    "VERSION_BUILD=$$VERSION_BUILD" \
    "APP_VERSION=\\\"$$VERSION\\\""

SOURCES += \
    src/AboutDialog.cpp \
    src/main.cpp \
    src/MainWindow.cpp

HEADERS += \
    include/MainWindow.h \
    src/AboutDialog.h

FORMS += \
    src/AboutDialog.ui \
    ui/MainWindow.ui

TRANSLATIONS += \
    i18n/wkhtml-gui_pl_PL.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

