#ifndef AUDIOINPUTFACTORY_H
#define AUDIOINPUTFACTORY_H
#include <QAudioInput>
#include <QDebug>

class AudioInputFactory
{
public:
  static QAudioInput * createAudioInput(const QAudioFormat & format, QObject * parent);
  static QAudioInput * createAudioInput(QObject * parent);
private:
  AudioInputFactory();
};

#endif // AUDIOINPUTFACTORY_H
