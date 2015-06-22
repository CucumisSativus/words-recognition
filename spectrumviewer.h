#ifndef SPECTRUMVIEWER_H
#define SPECTRUMVIEWER_H

#include <QWidget>
#include <QDateTime>
#include "defines.h"
namespace Ui {
  class SpectrumViewer;
}

class SpectrumViewer : public QWidget
{
  Q_OBJECT

public:
  explicit SpectrumViewer(const TransformedVectors & frames,QWidget *parent = 0);
  ~SpectrumViewer();
private slots:
  void comboBoxItemCHanges(int index);
private:
  Ui::SpectrumViewer *ui;
  TransformedVectors frames;
};

#endif // SPECTRUMVIEWER_H
