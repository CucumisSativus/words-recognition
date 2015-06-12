#include "frequencydomainfilter.h"

FrequencyDomainFilter::FrequencyDomainFilter(const TransformedVector &transformedFrame, unsigned long frameNumber, int samplingFrequency, int d) :
  m_frameNumber(frameNumber), m_samplingFrequency(samplingFrequency), m_transformedFrame(transformedFrame)
{
  m_c = calculateC();
  m_l = calculateL();
  m_r = calculateR();
}
double FrequencyDomainFilter::c() const
{
  return m_c;
}
double FrequencyDomainFilter::l() const
{
  return m_l;
}
double FrequencyDomainFilter::r() const
{
  return m_r;
}
int FrequencyDomainFilter::d() const
{
  return m_d;
}

void FrequencyDomainFilter::setD(int d)
{
  m_d = d;
}

FilteredFrame FrequencyDomainFilter::filter()
{
  FilteredFrame filteredFrame;
  for(TransformedVector::iterator it = m_transformedFrame.begin(); it != m_transformedFrame.end(); ++it){
      TransformedSample sample = *it;
      double filteredSample = 0;
      if(sample >= m_l && sample >= m_c){
          filteredSample = (sample - m_l)/(m_c - m_l);
        }
      else if (sample >= m_c && sample >= m_r) {
          filteredSample = (m_r - sample) / (m_r - m_c);
        }
      filteredFrame.push_back(filteredSample);
    }
}





double FrequencyDomainFilter::calculateMi(double m)
{
  return 700 * ( std::pow(10, m/2595) -1);
}

double FrequencyDomainFilter::calculateC()
{
  return calculateMi(m_frameNumber * m_d);
}

double FrequencyDomainFilter::calculateL()
{
  return calculateMi((m_frameNumber - 1) * m_d);
}

double FrequencyDomainFilter::calculateR()
{
  return calculateMi((m_frameNumber +1) * m_d);
}

