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
  QVector<double> x;
  for(unsigned long i =0; i< framesCoefficients.size(); ++i){
      x.push_back(i);
    }
  double yMin = 0;
  double yMax =0;
  unsigned long coefficientsNum = framesCoefficients.at(0).size();
  QVector< QVector<double> > coefficientsByFrame(coefficientsNum);

  ui->plot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
  ui->plot->legend->setVisible(true);
  QFont legendFont = font();  // start out with MainWindow's font..
  legendFont.setPointSize(9); // and make a bit smaller for legend
  ui->plot->legend->setFont(legendFont);
  ui->plot->legend->setBrush(QBrush(QColor(255,255,255,230)));
  QVector<QCPScatterStyle> lineStyles;
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssDot, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssCross, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssPlus, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssCircle, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssDisc, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssSquare, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssDiamond, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssStar, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssTriangle, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssTriangleInverted, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssCrossSquare, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssPlusSquare, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssPlusCircle, 4) );
  lineStyles.push_back(QCPScatterStyle(QCPScatterStyle::ssPeace, 4));


  for(unsigned long i =0; i< coefficientsNum; ++i){
      for(unsigned long j=0; j< framesCoefficients.size(); ++j){
          double currenty = framesCoefficients.at(j).at(i);
          if(currenty > yMax) yMax = currenty;
          if(currenty < yMin) yMin = currenty;
          coefficientsByFrame[i].push_back(currenty);
        }
    }
  for(int coefficientIndex =0; coefficientIndex < coefficientsByFrame.size(); ++coefficientIndex){
    ui->plot->addGraph();
    ui->plot->graph(coefficientIndex)->setData(x,coefficientsByFrame.at(coefficientIndex));
    ui->plot->graph(coefficientIndex)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(coefficientIndex)->setScatterStyle(lineStyles.at(coefficientIndex % lineStyles.size()));
    ui->plot->graph(coefficientIndex)->setName(QString::number(coefficientIndex));
//    ui->plot->graph()->setBrush(QBrush(QColor(255,160,50,150)));
   }

  ui->plot->xAxis->setRange(0, x.size());
  ui->plot->yAxis->setRange(yMin, yMax);
  ui->plot->replot();
}
