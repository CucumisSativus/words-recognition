#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T21:23:08
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = words-recognition
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -Werror
LIBS += -L/usr/local/lib -lfftw3 -lm

INCLUDEPATH += /usr/local/include

SOURCES += main.cpp\
        mainwindow.cpp \
    audiohandler.cpp \
    factories/audioinputfactory.cpp \
    analyser/audioanalyser.cpp \
    analyser/frequencydomainfilter.cpp \
    mfcccoefficientsviewer.cpp

HEADERS  += mainwindow.h \
    audiohandler.h \
    factories/audioinputfactory.h \
    analyser/audioanalyser.h \
    defines.h \
    analyser/frequencydomainfilter.h \
    mfcccoefficientsviewer.h

FORMS    += mainwindow.ui \
    mfcccoefficientsviewer.ui
