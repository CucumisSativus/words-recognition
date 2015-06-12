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

  ui->buttonStop->setEnabled(false);
  ui->buttonAnalyse->setEnabled(false);
}

MainWindow::~MainWindow()
{
  delete ui;
  if(analyser){
      delete analyser;
    }
}

void MainWindow::startRecording()
{
  handler->startRecording();
  ui->buttonStop->setEnabled(true);
  ui->buttonStart->setEnabled(false);
}

void MainWindow::stopRecording()
{
  handler->stopRecording();
  ui->buttonStop->setEnabled(false);
  ui->buttonStart->setEnabled(true);
}

void MainWindow::performAnalysis()
{
  handler->prepareSamples();
  DataVector stdSampled = handler->samples().toStdVector();
  analyser = new AudioAnalyser(stdSampled);
}
