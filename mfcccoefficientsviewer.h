#ifndef MFCCCOEFFICIENTSVIEWER_H
#define MFCCCOEFFICIENTSVIEWER_H

#include <QWidget>
#include <QDateTime>
#include "defines.h"
namespace Ui {
  class MfccCoefficientsViewer;
}

class MfccCoefficientsViewer : public QWidget
{
  Q_OBJECT

public:
  explicit MfccCoefficientsViewer(const FilteredFrames &framesCoefficients, QWidget *parent = 0);
  ~MfccCoefficientsViewer();

private:
  Ui::MfccCoefficientsViewer *ui;

  void setupTable();
  void insertCoefficients(unsigned long frameNum, const FilteredFrame & coefficients);\
  void insertDataToPlot(const FilteredFrames & framesCoefficients);
};

#endif // MFCCCOEFFICIENTSVIEWER_H
