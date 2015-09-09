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
  connect(ui->buttonLoad, SIGNAL(pressed()), this, SLOT(analyseFile()));
  connect(ui->buttonCompare, SIGNAL(pressed()), this, SLOT(compareSamples()));

  ui->buttonStop->setEnabled(false);
  ui->buttonAnalyse->setEnabled(false);
  ui->buttonPlay->setEnabled(false);
  ui->buttonCompare->setEnabled(false);
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
  if(handler){
      delete handler;
    }
  handler = new AudioHandler(AudioInputFactory::createAudioInput(this), this);
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
  if(SampleDbInstance.resultsCount() >= 2){
      ui->buttonCompare->setEnabled(true);
    }
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
  SampleDbInstance.appendResults(QDateTime::currentDateTime().toString(), coefficients);
  qDebug() << "coefficient calculation finished";
  coefficientsWindows.push_back(new MfccCoefficientsViewer(coefficients));
  coefficientsWindows.last()->show();

  spectrumWindows.push_back(new SpectrumViewer(analyser->transformedFrames()));
  spectrumWindows.last()->show();
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
  outputBuffer = new QBuffer(new QByteArray(handler->rawSamples()));
  outputBuffer->open(QIODevice::ReadOnly);
  audioOutput->start(outputBuffer);
  ui->buttonPlay->setEnabled(false);
}

void MainWindow::analyseFile()
{
  QAudioDecoder *decoder = new QAudioDecoder(this);
  decoder->setAudioFormat(AudioInputFactory::createFormat());
  decoder->setSourceFilename("/Users/michal/uczelnia/sound-processing/words-recognition/samples/raz.wav");
  qDebug() << "Audio file duration" << decoder->duration();
  qDebug() << decoder->error();
  f_handler = new FileHandler(decoder);
  connect(f_handler, SIGNAL(samplesReady()), this, SLOT(fileSamplesReady()));
  f_handler->prepareSamples();
}

void MainWindow::compareSamples()
{
  QMessageBox msgBox;
  QString closestSampleName = SampleDbInstance.compareLastSample();
  msgBox.setText(closestSampleName);
  msgBox.exec();
}

void MainWindow::audioOutputStateCHanged(QAudio::State newState)
{
  switch (newState) {
          case QAudio::IdleState:
              // Finished playing (no more data)
              audioOutput->stop();
              outputBuffer->close();
              delete outputBuffer;
              delete audioOutput;
              break;

          case QAudio::StoppedState:

              // Stopped for other reasons
              if (audioOutput->error() != QAudio::NoError) {
                  qWarning() << "playback stopped with errors";
                  qWarning() << audioOutput->error();
              }
              qDebug() << "playback stopped without errors";
              ui->buttonPlay->setEnabled(true);
              break;

          default:
              // ... other cases as appropriate
              break;
    }
}

void MainWindow::fileSamplesReady()
{
  DataVector stdSampled = f_handler->samples().toStdVector();
  analyser = new AudioAnalyser(stdSampled);
  FilteredFrames coefficients = analyser->mfccCoefficents(30, 100);
  coefficientsWindows.push_back(new MfccCoefficientsViewer(coefficients));
  coefficientsWindows.last()->show();

  spectrumWindows.push_back(new SpectrumViewer(analyser->transformedFrames()));
  spectrumWindows.last()->show();
}
