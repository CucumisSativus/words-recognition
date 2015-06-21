#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioOutput>
#include "audiohandler.h"
#include "factories/audioinputfactory.h"
#include "analyser/audioanalyser.h"
#include "mfcccoefficientsviewer.h"

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

  void audioOutputStateCHanged(QAudio::State newState);
private:
  Ui::MainWindow *ui;
  AudioHandler * handler;
  AudioAnalyser * analyser;
  QAudioOutput * audioOutput;
  QVector<MfccCoefficientsViewer * > coefficientsWindows;
};

#endif // MAINWINDOW_H
