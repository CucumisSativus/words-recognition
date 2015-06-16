#ifndef MFCCCOEFFICIENTSVIEWER_H
#define MFCCCOEFFICIENTSVIEWER_H

#include <QWidget>

namespace Ui {
  class MfccCoefficientsViewer;
}

class MfccCoefficientsViewer : public QWidget
{
  Q_OBJECT

public:
  explicit MfccCoefficientsViewer(QWidget *parent = 0);
  ~MfccCoefficientsViewer();

private:
  Ui::MfccCoefficientsViewer *ui;
};

#endif // MFCCCOEFFICIENTSVIEWER_H
