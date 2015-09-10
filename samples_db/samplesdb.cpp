#include "samplesdb.h"

SamplesDb::SamplesDb(QObject * parent) : QObject(parent)
{

}

void SamplesDb::appendResults(const QString &name, const FilteredFrames &results)
{
  this->results.push_back(CoefficientsResult(name, results));
}

QString SamplesDb::closestSample(const FilteredFrames & recorded)
{
  DistancePairs costs;
  CoefficientsResult queried("", recorded);
  for(int i = 0; i< results.size(); ++i){
      CoefficientsResult fromDb = results.at(i);
      QString name = fromDb.first;
      DtwMatrix matrix(fromDb, queried);
      matrix.printCosts();
      qDebug() << "==============Path==============";
      matrix.printPath();
      costs.push_back(DistancePair(name, matrix.cost(BAND_COEFFICIENT)));
    }

  return closestDistanceSampleName(costs);
}

QString SamplesDb::compareLastSample()
{
  return closestSample(results.last().second);
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
      qDebug() << "Distance to "<< pairs[i].first << " : " << distance;
      if(distance < minDistance && distance != 0){
          minDistance = distance;
          closestDistanceSampleName = pairs[i].first;
        }
    }
  return closestDistanceSampleName;
}

