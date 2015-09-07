#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <QAudioBuffer>
#include "defines.h"

class FileHandler : public QObject
{
  Q_OBJECT
public:
  explicit FileHandler(QAudioDecoder *decoder, QObject *parent = 0);

  QVector<DataType> samples() const;

signals:
  void samplesReady();
public slots:
  void prepareSamples();
private slots:
  void readBuffer();
private:
  QVector<DataType> m_samples;
  QAudioDecoder * m_decoder;
  QAudioFormat m_format;
};

#endif // FILEHANDLER_H
