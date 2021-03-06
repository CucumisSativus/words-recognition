#include "audiohandler.h"

AudioHandler::AudioHandler(QAudioInput *audioInput, QObject *parent) : QObject(parent), m_audioInput(audioInput)
{
  m_samplingFrequency = m_audioInput->format().sampleRate();
  connect(m_audioInput, SIGNAL(stateChanged(QAudio::State)), this, SLOT(audioInputStateChanged(QAudio::State)));
}

AudioHandler::~AudioHandler()
{
  if(m_recording){
      m_audioInput -> stop();
    }
}

bool AudioHandler::recording() const
{
  return m_recording;
}
QIODevice *AudioHandler::recordingDevice() const
{
  return m_recordingDevice;
}
QVector<DataType> AudioHandler::samples() const
{
  return m_samples;
}

QAudioFormat AudioHandler::format() const
{
  return m_audioInput->format();
}
int AudioHandler::samplingFrequency() const
{
  return m_samplingFrequency;
}
QByteArray AudioHandler::rawSamples() const
{
  return m_rawSamples;
}




void AudioHandler::appendAudioRead(const QByteArray &arr)
{
  m_rawSamples.append(arr);
  qDebug() << "appending audio, current size" << m_rawSamples.size();
}

void AudioHandler::prepareSamples(const QByteArray &rawSamples, const QAudioFormat &format)
{
  QAudioBuffer buffer(rawSamples, format);
  qDebug() << "Buffer duration" << buffer.duration()/1000000.0;
  const QAudioBuffer::S32F *data = buffer.constData<QAudioBuffer::S32F>();
  qDebug() << "frameCount" << buffer.frameCount() << " samplesCount" << buffer.sampleCount();
  for(int i =0; i< buffer.frameCount(); ++i){
    //TODO: ogarnąć czemu to się wywala i co z ym zrobić
    const float sample = data[i].left;
    if(sample != 0.0){
        m_samples.push_back(sample);
      }
    }
}

void AudioHandler::audioInputStateChanged(QAudio::State newState)
{
  switch (newState) {
    case QAudio::StoppedState:
      if (m_audioInput->error() != QAudio::NoError) {
          qWarning() << "Audio input Error!" << m_audioInput->error();
        } else {
          qDebug() << "Recording finished";
        }
      break;

    case QAudio::ActiveState:
      qDebug() << "Recording started";
      connect(m_audioInput, SIGNAL(notify()), this, SLOT(audioReadReady()));
      break;
    default:
      break;
    }
}


void AudioHandler::startRecording()
{
  m_rawSamples.clear();
  m_samples.clear();
  m_recording = true;
  m_recordingDevice =  m_audioInput->start();
}

void AudioHandler::stopRecording()
{
  m_recording = false;
  m_audioInput->stop();
  m_recordingDevice = nullptr;
}

void AudioHandler::audioReadReady()
{
  qDebug() << "Read ready";
  appendAudioRead(m_recordingDevice->readAll());
}

void AudioHandler::prepareSamples()
{
  prepareSamples(m_rawSamples, m_audioInput->format());
}

