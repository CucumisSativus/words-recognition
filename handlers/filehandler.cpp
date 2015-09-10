#include "filehandler.h"

FileHandler::FileHandler(const QString & filename, QObject *parent) :
  QObject(parent), filename(filename)
{
  if (!(infileHandle = SndfileHandle(filename.toStdString(), SFM_READ))) {
          throw std::runtime_error("Cannot open input file");
      };
}

void FileHandler::prepareSamples()
{
  sf_count_t readCount;
  while((readCount = (read(data))) != 0){
      std::vector<double> vector(data, data + readCount);
      m_samples.reserve(m_samples.size() + vector.size());
      m_samples.insert(m_samples.end(), vector.begin(), vector.end());
  }
  emit samplesReady(filename);
}

sf_count_t FileHandler::read(double *data)
{
  return infileHandle.read(data, BUFFER_LEN);
}

QVector<DataType> FileHandler::samples() const
{
  return QVector<DataType>::fromStdVector(m_samples);
}


