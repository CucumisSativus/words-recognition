#include "samplesdb.h"

SamplesDb::SamplesDb(QObject * parent) : QObject(parent)
{

}

void SamplesDb::appendResults(const QString &name, const FilteredFrames &results)
{
  this->results.push_back(CoefficientsResult(name, results));
}

QString SamplesDb::closestSample(const QString &name)
{
  CoefficientsResult queried;
  for(int i =0; i< results.size(); ++i){
      if(results[i].first == name){
          queried = results[i];
        }
    }
  CoefficientsResults resultsExcludingQueried = results;
  resultsExcludingQueried.removeAll(queried);
  DistancePairs costs;
  for(int i = 0; i< resultsExcludingQueried.size(); ++i){
      CoefficientsResult fromDb;
      QString name = fromDb.first;
      DtwMatrix matrix(fromDb, queried);
      costs.push_back(DistancePair(name, matrix.cost(BAND_COEFFICIENT)));
    }

  return closestDistanceSampleName(costs);
}

QString SamplesDb::compareLastSample()
{
  return closestSample(results.last().first);
}

unsigned long SamplesDb::resultsCount()
{
  return results.size();
}

QString SamplesDb::closestDistanceSampleName(const DistancePairs &pairs)
{
  double minDistance = std::numeric_limits<double>::max();
  QString closestDistanceSampleName = pairs[0].first;
  for(int i =0; i<pairs.size(); ++i){
      double distance = pairs[i].second;
      if(distance < minDistance){
          minDistance = distance;
          closestDistanceSampleName = pairs[i].first;
        }
    }
  return closestDistanceSampleName;
}

