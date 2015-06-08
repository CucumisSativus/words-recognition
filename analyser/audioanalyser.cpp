#include "audioanalyser.h"




AudioAnalyser::AudioAnalyser(const DataVector &samples)
{

}

DataVectors AudioAnalyser::dividedSamples() const
{
  return m_dividedSamples;
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
        DataType value = alpha - beta * std::cos((2 * M_1_PI * i)/(FRAME_SIZE -1));
        _frame.push_back(value);
      }
}
