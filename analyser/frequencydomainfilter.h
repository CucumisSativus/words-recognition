#ifndef FREQUENCYDOMAINFILTER_H
#define FREQUENCYDOMAINFILTER_H

#include <cmath>
#include "../defines.h"

class FrequencyDomainFilter
{
public:
  FrequencyDomainFilter(const TransformedVector &transformedFrame, unsigned long frameNumber, int samplingFrequency = 44100, int d =100);
  double c() const;

  double l() const;

  double r() const;

  int d() const;
  void setD(int d);

  FilteredFrame filter();
private:
  int m_frameNumber;
  int m_samplingFrequency;
  int m_d;

  double m_c;
  double m_l;
  double m_r;
  TransformedVector m_transformedFrame;
  double calculateMi(double m);
  double calculateC();
  double calculateL();
  double calculateR();
};

#endif // FREQUENCYDOMAINFILTER_H
