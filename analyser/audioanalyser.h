#ifndef AUDIOANALYSER_H
#define AUDIOANALYSER_H

#include <vector>
#include <cmath>
#include "../defines.h"

typedef std::vector<DataVector> DataVectors;
class AudioAnalyser
{
public:
  const unsigned int FRAME_SIZE = 1024;
  ///
  /// \brief AudioAnalyser class responsible for anlysing audio samples
  /// \param samples vector of ready to use audio samples
  ///
  AudioAnalyser(const DataVector & samples);
  DataVectors dividedSamples() const;
private:
  DataVectors m_dividedSamples;
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
};

#endif // AUDIOANALYSER_H
