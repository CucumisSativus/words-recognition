#ifndef AUDIOANALYSER_H
#define AUDIOANALYSER_H

#include <vector>
#include <cmath>
#include <fftw3.h>
#include "../defines.h"
class AudioAnalyser
{
public:
  const unsigned int FRAME_SIZE = 1024;
  ///
  /// \brief AudioAnalyser class responsible for anlysing audio samples
  /// \param samples vector of ready to use audio samples
  /// \param samplingFrequency sampling frequency of the audio
  ///
  AudioAnalyser(const DataVector & samples, int samplingFrequency = 44100);
  DataVectors dividedSamples() const;
  TransformedVectors transformedFrames() const;

private:
  DataVectors m_dividedSamples;
  TransformedVectors m_transformedFrames;

  ///
  /// \brief divideSamples function which divides samples obtained form the constructor
  /// into smaller vector with size at most FRAME_SIZE
  /// \param samples vector of ready to use audio samples
  ///
  void divideSamples(const DataVector &samples);
  ///
  /// \brief applyHammingWindow function which applies Hamming window on given frame
  /// \param frame frame consisting of samples
  /// \return frame with applied Hamming Window function
  ///
  DataVector applyHammingWindow(const DataVector & frame);
  void transformFrames(const DataVectors & frames);
  ///
  /// \brief computeFft function which computes fft on given frames
  /// \param frames frames with hamming window applied
  /// \return
  ///
  TransformedVectors calculateMagnitudeSpectrum(const DataVectors & frames);
};

#endif // AUDIOANALYSER_H
