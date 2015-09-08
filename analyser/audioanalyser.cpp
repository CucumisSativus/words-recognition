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
  for(unsigned long i=1; i< m_transformedFrames.size(); ++i){
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
      if(!std::isnan(*it)){
        frame.push_back(*it);
        }
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
        DataType value = alpha - beta * std::cos((2 * M_PI * frame.at(i))/(FRAME_SIZE -1)) * frame.at(i);
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
  //TODO: wykresy po DFT, w skali melowej, po cosinusach
  for(unsigned long frameIndex =0; frameIndex < frames.size(); ++frameIndex){
      TransformedVector transformedFrameVector;
      DataVector frame = frames.at(frameIndex);
      unsigned long dataSize = frame.size();

      double *frameToBeTransformed = (double *) fftw_malloc(sizeof(double) * dataSize);
      fftw_complex *transformedFrame = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * dataSize);

//      std::copy(frame.begin(), frame.end(), frameToBeTransformed);
      unsigned nanCounter = 0;
      for(unsigned int i =0; i < frame.size(); ++i){
          double sample = frame.at(i);
          if(std::isnan(sample) ){
              std::cout << "we have a nan over here!" << std::endl;
              nanCounter++;
            }
          if(std::isinf(sample)){
              std::cout << "we have an infinity over here!" << std::endl;
            }
          frameToBeTransformed[i] = frame.at(i);
        }
      if(nanCounter != 0){
          std::cout << "nan ratio:" << (double)nanCounter/frame.size();
        }
      fftw_plan plan = fftw_plan_dft_r2c_1d(dataSize, frameToBeTransformed, transformedFrame, FFTW_MEASURE);
      fftw_execute(plan);

      nanCounter =0;
      for(unsigned long i=0; i< dataSize/2; ++i){
          double realPart = transformedFrame[i][0];
          double imagPart = transformedFrame[i][1];

          if(std::isnan(realPart) || std::isnan(imagPart)){
              std::cout << "we have a nan over here!" << std::endl;
              nanCounter++;
            }
          if(std::isinf(realPart) || std::isinf(imagPart)){
              std::cout << "we have an infinity over here!" << std::endl;
            }
          double magnitude = hypot(realPart, imagPart) / (dataSize/2);
          transformedFrameVector.push_back( magnitude );
        }

      if(nanCounter != 0){
          std::cout << "nan ratio after transformation:" << (double)nanCounter/frame.size();
        }
      transformedFrames.push_back(transformedFrameVector);
      fftw_destroy_plan(plan);
      fftw_free(frameToBeTransformed);
      fftw_free(transformedFrame);
    }
  return transformedFrames;
}
