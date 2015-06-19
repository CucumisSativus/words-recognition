#include "audioanalyser.h"




AudioAnalyser::AudioAnalyser(const DataVector &samples, int samplingFrequency) : m_samplingFrequency(samplingFrequency)
{
  divideSamples(samples);
  transformFrames(m_dividedSamples);
}

DataVectors AudioAnalyser::dividedSamples() const
{
  return m_dividedSamples;
}
TransformedVectors AudioAnalyser::transformedFrames() const
{
  return m_transformedFrames;
}
int AudioAnalyser::samplingFrequency() const
{
  return m_samplingFrequency;
}

FilteredFrames AudioAnalyser::mfccCoefficents(unsigned long filterOrder, int distanceBetweenFilters) const
{
  FilteredFrames frames;
  for(unsigned long i=0; i< m_transformedFrames.size(); ++i){
//  for(unsigned long i=0; i< 2; ++i){
    FrequencyDomainFilter filter(m_transformedFrames.at(i), filterOrder, m_samplingFrequency, distanceBetweenFilters);
    frames.push_back(filter.filter());
    }
  return frames;
}



void AudioAnalyser::divideSamples(const DataVector & samples)
{
  DataVector frame;
  for(DataVector::const_iterator it = samples.begin(); it != samples.end(); ++it)
    {
      frame.push_back(*it);
      if(frame.size() >= FRAME_SIZE){
          m_dividedSamples.push_back(applyHammingWindow(frame));
          frame.clear();
        }
    }
}

DataVector AudioAnalyser::applyHammingWindow(const DataVector &frame)
{
    DataVector _frame;
    double alpha = 0.54;
    double beta = 1 - alpha;
    for(unsigned long i=0; i<frame.size(); ++i){
        DataType value = alpha - beta * std::cos((2 * M_PI * i)/(FRAME_SIZE -1));
        _frame.push_back(value);
      }
    return _frame;
}

void AudioAnalyser::transformFrames(const DataVectors &frames)
{
  m_transformedFrames = calculateMagnitudeSpectrum(frames);
}

TransformedVectors AudioAnalyser::calculateMagnitudeSpectrum(const DataVectors &frames)
{
  TransformedVectors transformedFrames;
  for(unsigned long frameIndex =0; frameIndex < frames.size(); ++frameIndex){
      TransformedVector transformedFrameVector;
      DataVector frame = frames.at(frameIndex);
      unsigned long dataSize = frame.size();

      double *frameToBeTransformed = (double *) fftw_malloc(sizeof(double) * dataSize);
      fftw_complex *transformedFrame = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * dataSize);

      std::copy(frame.begin(), frame.begin() + dataSize, frameToBeTransformed);

      fftw_plan plan = fftw_plan_dft_r2c_1d(dataSize, frameToBeTransformed, transformedFrame, FFTW_MEASURE);
      fftw_execute(plan);
      fftw_destroy_plan(plan);

      for(unsigned long i=0; i< dataSize; ++i){
          double realPart = transformedFrame[i][0];
          double imagPart = transformedFrame[i][1];
          transformedFrameVector.push_back( std::sqrt(realPart * realPart + imagPart + imagPart  ) );
        }

      transformedFrames.push_back(transformedFrameVector);
      fftw_free(frameToBeTransformed);
      fftw_free(transformedFrame);
    }
  return transformedFrames;
}
