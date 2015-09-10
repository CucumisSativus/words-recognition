#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <sndfile.hh>
#include <stdexcept>
#include "defines.h"

const int BUFFER_LEN = 1024;
class FileHandler : public QObject
{
  Q_OBJECT
public:
  explicit FileHandler(const QString &filename, QObject *parent = 0);

  QVector<DataType> samples() const;

signals:
  void samplesReady(QString);
public slots:
  void prepareSamples();
private:
  std::vector<double> m_samples;
  SndfileHandle infileHandle;
  double data[BUFFER_LEN];
  sf_count_t read(double * data);
  QString filename;
};

#endif // FILEHANDLER_H
