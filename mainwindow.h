#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
private:
  Ui::MainWindow *ui;
  AudioHandler * handler;
  AudioAnalyser * analyser;
  MfccCoefficientsViewer * viewer;
};

#endif // MAINWINDOW_H
