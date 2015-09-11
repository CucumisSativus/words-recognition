#include "samplesdb.h"

SamplesDb::SamplesDb(QObject * parent) : QObject(parent)
{
  readFromFile();
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
      double cost = matrix.cost(BAND_COEFFICIENT);
//      matrix.printCosts();
//      matrix.printPath();
      costs.push_back(DistancePair(name, cost));
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

void SamplesDb::saveToFile()
{
  QFile file( this->serializedFilePath );
  file.open( QIODevice::WriteOnly );

  QDataStream stream( &file );
  stream << results;
  file.close();
}

void SamplesDb::readFromFile()
{
  QFile file( this->serializedFilePath );
  if(file.open( QIODevice::ReadOnly )){
    QDataStream stream( &file );
    stream >> results;
    file.close();
    }

}



QString SamplesDb::closestDistanceSampleName(const DistancePairs &pairs)
{
  QVector< std::pair<std::string, double> > stdPairs;
  for(int i =0; i<pairs.size(); ++i){
      stdPairs.push_back(std::pair<std::string, double>(pairs[i].first.toStdString(), pairs[i].second));
    }
  qSort(stdPairs.begin(), stdPairs.end(), lessThan);
  qDebug() << "==================Distanced begin================";
  for(int i =0; i<pairs.size(); ++i){
      double distance = stdPairs[i].second;
      qDebug() << "Distance to "<< QString::fromStdString(stdPairs[i].first) << " : " << distance;
    }
  qDebug() << "==================Distanced end==================";
  return QString::fromStdString(stdPairs[0].first);
}

bool lessThan(const std::pair<std::string, double> &r1, const std::pair<std::string, double> &r2)
{
  return (r1.second < r2.second);
}
