#include "frequencydomainfilter.h"

FrequencyDomainFilter::FrequencyDomainFilter(const TransformedVector &transformedFrame, unsigned long filterOrder, int samplingFrequency, int distanceBetweenFilters) :
  m_filterOrder(filterOrder), m_samplingFrequency(samplingFrequency), m_distanceBetweenFilters(distanceBetweenFilters), m_transformedFrame(transformedFrame)
{
}

FilteredFrame FrequencyDomainFilter::filter()
{
  FilteredFrame filteredFrame;
  for(unsigned long i =0 ; i < m_transformedFrame.size()/2; ++i){
      double sample = m_transformedFrame.at(i);
      double filterResult = filterBank((m_samplingFrequency/m_transformedFrame.size() * i ));
      filteredFrame.push_back(sample * filterResult);
   }
  return filteredFrame;
}
int FrequencyDomainFilter::distanceBetweenFilters() const
{
  return m_distanceBetweenFilters;
}

void FrequencyDomainFilter::setDistanceBetweenFilters(int distanceBetweenFilters)
{
  m_distanceBetweenFilters = distanceBetweenFilters;
}

double FrequencyDomainFilter::calculateMi(double m)
{
  return 700 * ( std::pow(10, m/2595) -1);
}

double FrequencyDomainFilter::calculateC(int k)
{
  return calculateMi(k * m_distanceBetweenFilters);
}

double FrequencyDomainFilter::calculateL(int k)
{
  return calculateMi((k - 1) * m_distanceBetweenFilters);
}

double FrequencyDomainFilter::calculateR(int k)
{
  return calculateMi((k +1) * m_distanceBetweenFilters);
}

double FrequencyDomainFilter::filterBank(double sample)
{
  double result =0;
  for(int k=0; k< m_filterOrder; ++k){
      result += orderFilterBank(k, sample);
    }
  return result;
}

double FrequencyDomainFilter::orderFilterBank(int order, int sample)
{
    double c = calculateC(order);
    double l = calculateL(order);
    double r = calculateR(order);

    if(sample >= l && sample >= c){
        return (sample - l)/(c - l);
      }
    else if (sample >= c && sample >= r) {
        return (r - sample) / (r - c);
      }
    else{
        return 0;
      }
}

