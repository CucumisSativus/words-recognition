#ifndef FREQUENCYDOMAINFILTER_H
#define FREQUENCYDOMAINFILTER_H

#include <cmath>
#include "../defines.h"

class FrequencyDomainFilter
{
public:
  FrequencyDomainFilter(const TransformedVector &transformedFrame, unsigned long filterOrder, int samplingFrequency = 44100, int distanceBetweenFilters =100);

  FilteredFrame filter();
  int distanceBetweenFilters() const;
  void setDistanceBetweenFilters(int distanceBetweenFilters);

private:
  unsigned long m_filterOrder;
  int m_samplingFrequency;
  int m_distanceBetweenFilters;

  TransformedVector m_transformedFrame;
  double calculateMi(double m);
  double calculateC(int k);
  double calculateL(int k);
  double calculateR(int k);
  double filterBank(double sample, unsigned long filterLevel);
  double orderFilterBank(int order, int sample);
  double amplitudeInMells(unsigned long k);

  unsigned long obtainF();
  double obtainGamma();

};

#endif // FREQUENCYDOMAINFILTER_H
