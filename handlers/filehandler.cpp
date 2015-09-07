#include "filehandler.h"

FileHandler::FileHandler(QAudioDecoder * decoder, QObject *parent) :
  QObject(parent),
  m_decoder(decoder),
  m_format(decoder->audioFormat())
{

}

void FileHandler::prepareSamples()
{
 connect(m_decoder, SIGNAL(bufferReady()), this, SLOT(readBuffer()));
 m_decoder->start();
}

void FileHandler::readBuffer()
{
  QAudioBuffer buffer = m_decoder->read();
  double *data = buffer.data<DataType>();
  for(int i=0; i< buffer.sampleCount(); ++i){
      m_samples.push_back(data[i]);
    }
  emit samplesReady();
}
QVector<DataType> FileHandler::samples() const
{
  return m_samples;
}


