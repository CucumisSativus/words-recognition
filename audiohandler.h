#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <QObject>
#include <QAudioInput>
#include <QAudioFormat>
#include <QAudioBuffer>
#include <QDebug>

#include "defines.h"
class AudioHandler : public QObject
{
  Q_OBJECT
public:
  ///
  /// \brief AudioHandler class responsible for handling audio
  /// \param audioInput input from which audio should be recorded
  /// \param parent parent of this object
  ///
  explicit AudioHandler(QAudioInput * audioInput, QObject *parent = 0);
  ~AudioHandler();
  ///
  /// \brief recording
  /// \return returns true if the recording is in progress
  ///
  bool recording() const;
  ///
  /// \brief recordingDevice
  /// \return returns device which obtains raw samples from audioInpit
  ///
  QIODevice *recordingDevice() const;

  ///
  /// \brief samples
  /// \return samples ready to be analysed, type is defined in defines.h
  ///
  QVector<DataType> samples() const;

  QAudioFormat format() const;
  int samplingFrequency() const;

  QByteArray rawSamples() const;

private:
  QAudioInput * m_audioInput;
  QIODevice * m_recordingDevice;
  bool m_recording;
  QByteArray m_rawSamples;
  QDataVector m_samples;
  int m_samplingFrequency;

  void appendAudioRead(const QByteArray & arr);
  ///
  /// \brief prepareSamples function which converts raw bytes into ready to use samples
  /// \param rawSamples raw bytes obtained from QIODevice connected to audioInput
  /// \param format format in which raw samples were taken
  ///
  void prepareSamples(const QByteArray & rawSamples, const QAudioFormat & format);
signals:

private slots:
  void audioInputStateChanged(QAudio::State newState);
  void audioReadReady();
public slots:
  void startRecording();
  void stopRecording();
  void prepareSamples();
};

#endif // AUDIOHANDLER_H
