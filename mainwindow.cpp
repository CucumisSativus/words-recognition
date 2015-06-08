#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  handler = new AudioHandler(AudioInputFactory::createAudioInput(this), this);

  connect(ui->buttonStart, SIGNAL(pressed()), this, SLOT(startRecording()));
  connect(ui->buttonStop, SIGNAL(pressed()), this, SLOT(stopRecording()));
  connect(ui->buttonAnalyse, SIGNAL(pressed()), this, SLOT(performAnalysis()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::startRecording()
{
  handler->startRecording();
}

void MainWindow::stopRecording()
{
  handler->stopRecording();
}

void MainWindow::performAnalysis()
{
  handler->prepareSamples();
}
