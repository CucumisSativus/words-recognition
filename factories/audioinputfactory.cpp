#include "audioinputfactory.h"

QAudioInput *AudioInputFactory::createAudioInput(const QAudioFormat &format, QObject *parent)
{
  QAudioInput * audio = new QAudioInput(format, parent);
  audio->setNotifyInterval(100);
  return audio;
}

QAudioInput *AudioInputFactory::createAudioInput(QObject *parent)
{
  QAudioFormat format;
  // Set up the desired format, for example:
  format.setSampleRate(44100);
  format.setChannelCount(1);
  format.setSampleSize(16);
  format.setCodec("audio/pcm");
  format.setByteOrder(QAudioFormat::LittleEndian);
  format.setSampleType(QAudioFormat::SignedInt);

  QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
  if (!info.isFormatSupported(format)) {
      qWarning() << "Default format not supported, trying to use the nearest.";
      format = info.nearestFormat(format);
  }
  return createAudioInput(format, parent);
}

AudioInputFactory::AudioInputFactory()
{

}

