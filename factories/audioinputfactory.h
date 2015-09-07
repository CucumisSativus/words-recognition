#ifndef AUDIOINPUTFACTORY_H
#define AUDIOINPUTFACTORY_H
#include <QAudioInput>
#include <QDebug>

class AudioInputFactory
{
public:
  static QAudioInput * createAudioInput(const QAudioFormat & format, QObject * parent);
  static QAudioInput * createAudioInput(QObject * parent);
  static QAudioFormat createFormat();
private:
  AudioInputFactory();
};

#endif // AUDIOINPUTFACTORY_H
