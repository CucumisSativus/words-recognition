#include "spectrumviewer.h"
#include "ui_spectrumviewer.h"

SpectrumViewer::SpectrumViewer(const TransformedVectors &frames, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SpectrumViewer),
  frames(frames)
{
  ui->setupUi(this);
  for(unsigned long i=0; i< frames.size();++i){
      ui->comboBoxChoseFrame->addItem(QString::number(i));
    }
  connect(ui->comboBoxChoseFrame, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxItemCHanges(int)));
}

SpectrumViewer::~SpectrumViewer()
{
  delete ui;
}

void SpectrumViewer::comboBoxItemCHanges(int index)
{
  if(index == -1) return;
  QVector<double> x,y;
  double currentX = 0;
  double yMin =0, yMax =0;
  for(unsigned long i =0; i < frames.at(index).size(); ++i){
      x.push_back(currentX++);
      double currenty = frames.at(index).at(i);
      if(currenty > yMax) yMax = currenty;
      if(currenty < yMin) yMin = currenty;
      y.push_back(currenty);
    }
  if(ui->plot->graphCount() !=0 ) ui->plot->removeGraph(0);
  ui->plot->addGraph();
  ui->plot->graph(0)->setData(x,y);
  ui->plot->xAxis->setRange(0, 30);
  ui->plot->yAxis->setRange(yMin, yMax);
  ui->plot->replot();
}
