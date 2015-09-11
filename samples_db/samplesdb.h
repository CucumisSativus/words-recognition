#ifndef SAMPLESDB_H
#define SAMPLESDB_H

#include <QObject>
#include <QVector>
#include <limits>
#include <QDebug>
#include <QFile>
#include <algorithm>
#include "singleton/singleton.h"
#include "../dtw/dtwmatrix.h"
#include "../defines.h"

bool lessThan(const std::pair<std::string, double> &r1, const std::pair<std::string, double> &r2);

class SamplesDb : public QObject
{
  Q_OBJECT
public:
  explicit SamplesDb(QObject *parent = 0);

  void appendResults(const QString & name, const FilteredFrames & results);
  QString closestSample(const FilteredFrames &recorded);
  QString compareLastSample();
  unsigned long resultsCount();
  void saveToFile();
  void readFromFile();

  CoefficientsResults results;

  double BAND_COEFFICIENT  = 1.0;
  const QString serializedFilePath = "/Users/michal/uczelnia/sound-processing/words-recognition/samples/serialized.dat";
private:
  QString closestDistanceSampleName(const DistancePairs & pairs);
signals:

public slots:
};
#define SampleDbInstance Singleton<SamplesDb>::instance()
#endif // SAMPLESDB_H
