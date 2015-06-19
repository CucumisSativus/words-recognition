#include "frequencydomainfilter.h"

FrequencyDomainFilter::FrequencyDomainFilter(const TransformedVector &transformedFrame, unsigned long filterOrder, int samplingFrequency, int distanceBetweenFilters) :
  m_filterOrder(filterOrder), m_samplingFrequency(samplingFrequency), m_distanceBetweenFilters(distanceBetweenFilters), m_transformedFrame(transformedFrame)
{
}

FilteredFrame FrequencyDomainFilter::filter()
{
  FilteredFrame filteredFrame;
  for(unsigned long n =0; n< obtainF(); ++n){
      double filterSum =0;
      for(unsigned long k =0; k < m_filterOrder - 1; ++k){
          double sK = bandpassFiltration(k);
          if(sK == 0){
              continue;
            }
          double lnSK = std::log(sK);
          double cosNumerator = (2.0 * M_PI * (2 * k +1) * n);
          double cosDenominator = 4.0 * m_filterOrder;
          double cosTrans = std::cos(cosNumerator/ cosDenominator);
          filterSum += std::pow(lnSK, obtainGamma()) * cosTrans;
        }
      filteredFrame.push_back(filterSum);
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

double FrequencyDomainFilter::filterBank(double sample, unsigned long filterLevel)
{
  double result =0;
  for(unsigned long k=0; k< filterLevel; ++k){
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

double FrequencyDomainFilter::bandpassFiltration(unsigned long k)
{
  double sum =0;
  for(unsigned long i =0 ; i < m_transformedFrame.size()/2; ++i){
      double sample = m_transformedFrame.at(i);
      double filterResult = filterBank((m_samplingFrequency/m_transformedFrame.size() * i ), k);
      sum += sample * filterResult;
    }
  return sum;
}

unsigned long FrequencyDomainFilter::obtainF()
{
  return 12;
}

double FrequencyDomainFilter::obtainGamma()
{
  return 1;
}

