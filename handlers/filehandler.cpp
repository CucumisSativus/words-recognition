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
  const QAudioBuffer::S32F *data = buffer.constData<QAudioBuffer::S32F>();
  for(int i =0; i< buffer.sampleCount(); ++i){
    const float sample = data[i].average();
    if(sample != 0.0){
        m_samples.push_back(sample);
      }
    }
  emit samplesReady();
}
QVector<DataType> FileHandler::samples() const
{
  return m_samples;
}


