#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T21:23:08
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = words-recognition
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -Werror
LIBS += -L/usr/local/lib -lfftw3 -lm
CONFIG += c++11
INCLUDEPATH += /usr/local/include

SOURCES += main.cpp\
        mainwindow.cpp \
    handlers/audiohandler.cpp \
    factories/audioinputfactory.cpp \
    analyser/audioanalyser.cpp \
    analyser/frequencydomainfilter.cpp \
    mfcccoefficientsviewer.cpp \
    qcustom-plot/qcustomplot.cpp \
    spectrumviewer.cpp \
    handlers/filehandler.cpp \
    samples_db/samplesdb.cpp

HEADERS  += mainwindow.h \
    handlers/audiohandler.h \
    factories/audioinputfactory.h \
    analyser/audioanalyser.h \
    defines.h \
    analyser/frequencydomainfilter.h \
    mfcccoefficientsviewer.h \
    qcustom-plot/qcustomplot.h \
    spectrumviewer.h \
    handlers/filehandler.h \
    samples_db/singleton/call_once.h \
    samples_db/singleton/singleton.h \
    samples_db/samplesdb.h

FORMS    += mainwindow.ui \
    mfcccoefficientsviewer.ui \
    spectrumviewer.ui
