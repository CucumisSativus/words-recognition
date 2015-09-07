#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioOutput>
#include <QBuffer>
#include <QAudioDecoder>

#include "handlers/audiohandler.h"
#include "handlers/filehandler.h"
#include "factories/audioinputfactory.h"
#include "analyser/audioanalyser.h"
#include "mfcccoefficientsviewer.h"
#include "spectrumviewer.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
private slots:
  void startRecording();
  void stopRecording();
  void performAnalysis();
  void playRecorded();
  void analyseFile();

  void audioOutputStateCHanged(QAudio::State newState);
  void fileSamplesReady();
private:

  Ui::MainWindow *ui;
  AudioHandler * handler;
  AudioAnalyser * analyser;
  QAudioOutput * audioOutput;
  QBuffer * outputBuffer;
  QVector<MfccCoefficientsViewer * > coefficientsWindows;
  QVector<SpectrumViewer * > spectrumWindows;
};

#endif // MAINWINDOW_H
