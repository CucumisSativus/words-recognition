#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  handler = new AudioHandler(AudioInputFactory::createAudioInput(this), this);
  analyser = nullptr;
  connect(ui->buttonStart, SIGNAL(pressed()), this, SLOT(startRecording()));
  connect(ui->buttonStop, SIGNAL(pressed()), this, SLOT(stopRecording()));
  connect(ui->buttonAnalyse, SIGNAL(pressed()), this, SLOT(performAnalysis()));
  connect(ui->buttonPlay, SIGNAL(pressed()), this, SLOT(playRecorded()));
  ui->buttonStop->setEnabled(false);
  ui->buttonAnalyse->setEnabled(false);
  ui->buttonPlay->setEnabled(false);
}

MainWindow::~MainWindow()
{
  delete ui;
  if(analyser){
      delete analyser;
    }
  if(handler->recording()){
      handler->stopRecording();
    }
}

void MainWindow::startRecording()
{
  handler->startRecording();
  ui->buttonStop->setEnabled(true);
  ui->buttonStart->setEnabled(false);
  ui->buttonAnalyse->setEnabled(false);
  ui->buttonPlay->setEnabled(false);
}

void MainWindow::stopRecording()
{
  handler->stopRecording();
  ui->buttonStop->setEnabled(false);
  ui->buttonStart->setEnabled(true);
  ui->buttonAnalyse->setEnabled(true);
  ui->buttonPlay->setEnabled(true);
}

void MainWindow::performAnalysis()
{
  qDebug() << "analysis started";
  handler->prepareSamples();
  qDebug() << "samples prepared";
  DataVector stdSampled = handler->samples().toStdVector();
  analyser = new AudioAnalyser(stdSampled);
  qDebug() << "coefficient calculation started";
  FilteredFrames coefficients = analyser->mfccCoefficents(30, 100);
  qDebug() << "coefficient calculation finished";
  coefficientsWindows.push_back(new MfccCoefficientsViewer(coefficients));
  coefficientsWindows.last()->show();
}

void MainWindow::playRecorded()
{
  qDebug() << "Playback started";
  QAudioFormat format = handler->format();
  QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
      if (!info.isFormatSupported(format)) {
          qWarning() << "Raw audio format not supported by backend, cannot play audio.";
          return;
      }
  audioOutput = new QAudioOutput(format, this);
  connect(audioOutput, SIGNAL(stateChanged(QAudio::State)), this, SLOT(audioOutputStateCHanged(QAudio::State)));
  audioOutput->start(handler->recordingDevice());
}

void MainWindow::audioOutputStateCHanged(QAudio::State newState)
{
  switch (newState) {
          case QAudio::IdleState:
              // Finished playing (no more data)
              audioOutput->stop();
              delete audioOutput;
              break;

          case QAudio::StoppedState:
              // Stopped for other reasons
              if (audioOutput->error() != QAudio::NoError) {
                  qWarning() << audioOutput->error();
              }
              break;

          default:
              // ... other cases as appropriate
              break;
      }
}
