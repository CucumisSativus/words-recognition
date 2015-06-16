#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow), viewer(nullptr)
{
  ui->setupUi(this);

  handler = new AudioHandler(AudioInputFactory::createAudioInput(this), this);
  analyser = nullptr;
  connect(ui->buttonStart, SIGNAL(pressed()), this, SLOT(startRecording()));
  connect(ui->buttonStop, SIGNAL(pressed()), this, SLOT(stopRecording()));
  connect(ui->buttonAnalyse, SIGNAL(pressed()), this, SLOT(performAnalysis()));

  ui->buttonStop->setEnabled(false);
  ui->buttonAnalyse->setEnabled(false);
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
}

void MainWindow::stopRecording()
{
  handler->stopRecording();
  ui->buttonStop->setEnabled(false);
  ui->buttonStart->setEnabled(true);
  ui->buttonAnalyse->setEnabled(true);
}

void MainWindow::performAnalysis()
{
  if(viewer){
      viewer->deleteLater();
      viewer = nullptr;
    }
  qDebug() << "analysis started";
  handler->prepareSamples();
  qDebug() << "samples prepared";
  DataVector stdSampled = handler->samples().toStdVector();
  analyser = new AudioAnalyser(stdSampled);
  qDebug() << "coefficient calculation started";
  FilteredFrames coefficients = analyser->mfccCoefficents(30, 100);
  qDebug() << "coefficient calculation finished";
  viewer = new MfccCoefficientsViewer(coefficients);
  viewer->show();
}
