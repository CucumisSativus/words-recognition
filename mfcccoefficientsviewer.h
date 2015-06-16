#ifndef MFCCCOEFFICIENTSVIEWER_H
#define MFCCCOEFFICIENTSVIEWER_H

#include <QWidget>
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
  void insertCoefficients(unsigned long frameNum, const FilteredFrame & coefficients);
};

#endif // MFCCCOEFFICIENTSVIEWER_H
