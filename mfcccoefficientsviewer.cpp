#include "mfcccoefficientsviewer.h"
#include "ui_mfcccoefficientsviewer.h"

MfccCoefficientsViewer::MfccCoefficientsViewer(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MfccCoefficientsViewer)
{
  ui->setupUi(this);
}

MfccCoefficientsViewer::~MfccCoefficientsViewer()
{
  delete ui;
}
