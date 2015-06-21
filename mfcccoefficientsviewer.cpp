#include "mfcccoefficientsviewer.h"
#include "ui_mfcccoefficientsviewer.h"

MfccCoefficientsViewer::MfccCoefficientsViewer(const FilteredFrames &framesCoefficients, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MfccCoefficientsViewer)
{
  ui->setupUi(this);
  setupTable();
  for(unsigned long i = 0; i< framesCoefficients.size(); ++i){
      insertCoefficients(i, framesCoefficients.at(i));
    }
  insertDataToPlot(framesCoefficients);
  ui->dateLabel->setText(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
}

MfccCoefficientsViewer::~MfccCoefficientsViewer()
{
  delete ui;
}

void MfccCoefficientsViewer::setupTable()
{
  ui->coefficientsTable->setColumnCount(3);
  QStringList labels;
  labels << tr("frame number") << tr("Num") << tr("Value");
  ui->coefficientsTable->setHorizontalHeaderLabels(labels);
//  ui->coefficientsTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
//  filesTable->verticalHeader()->hide();
  //  filesTable->setShowGrid(true);
}

void MfccCoefficientsViewer::insertCoefficients(unsigned long frameNum, const FilteredFrame &coefficients)
{
  for(unsigned long i =0; i< coefficients.size(); ++i){
      int row = ui->coefficientsTable->rowCount();
      ui->coefficientsTable->insertRow(row);
      QTableWidgetItem * frameNumberItem = new QTableWidgetItem();
      frameNumberItem->setText(QString::number(frameNum));

      QTableWidgetItem * numberItem = new QTableWidgetItem();
      numberItem->setText(QString::number(i));

      QTableWidgetItem * valueItem = new QTableWidgetItem();
      valueItem->setText(QString::number(coefficients.at(i)));


      ui->coefficientsTable->setItem(row, 0, frameNumberItem);
      ui->coefficientsTable->setItem(row, 1, numberItem);
      ui->coefficientsTable->setItem(row, 2, valueItem);
    }
}

void MfccCoefficientsViewer::insertDataToPlot(const FilteredFrames &framesCoefficients)
{
  QVector<double> x,y ;
  double currentX =0;
  for(unsigned long i =0; i< 2; ++i){
      for(unsigned long j=0; j< framesCoefficients.at(i).size(); ++j){
          x.push_back(currentX++);
          y.push_back(framesCoefficients.at(i).at(j));
        }
    }
  ui->plot->addGraph();
  ui->plot->graph(0)->setData(x,y);
  ui->plot->xAxis->setRange(0, currentX);
  ui->plot->replot();
}
