#include "audioinputfactory.h"

QAudioInput *AudioInputFactory::createAudioInput(const QAudioFormat &format, QObject *parent)
{
  QAudioInput * audio = new QAudioInput(format, parent);
  audio->setNotifyInterval(100);
  return audio;
}

QAudioInput *AudioInputFactory::createAudioInput(QObject *parent)
{

  QAudioFormat format = createFormat();

  QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
  if (!info.isFormatSupported(format)) {
      qWarning() << "Default format not supported, trying to use the nearest.";
      format = info.nearestFormat(format);
  }
  return createAudioInput(format, parent);
}

QAudioFormat AudioInputFactory::createFormat()
{
  QAudioFormat format;
  // Set up the desired format, for example:
  format.setSampleRate(44100);
  format.setChannelCount(1);
  format.setSampleSize(32);
  format.setCodec("audio/pcm");
  format.setByteOrder(QAudioFormat::LittleEndian);
  format.setSampleType(QAudioFormat::Float);
  if(!format.isValid()){
      throw 1;
    }
  return format;
}

AudioInputFactory::AudioInputFactory()
{

}

