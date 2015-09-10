#ifndef SAMPLESDB_H
#define SAMPLESDB_H

#include <QObject>
#include <QVector>
#include <limits>
#include <QDebug>
#include "singleton/singleton.h"
#include "../dtw/dtwmatrix.h"
#include "../defines.h"

class SamplesDb : public QObject
{
  Q_OBJECT
public:
  explicit SamplesDb(QObject *parent = 0);

  void appendResults(const QString & name, const FilteredFrames & results);
  QString closestSample(const FilteredFrames &recorded);
  QString compareLastSample();
  unsigned long resultsCount();

  CoefficientsResults results;

  double BAND_COEFFICIENT  = 1.0;
private:
  QString closestDistanceSampleName(const DistancePairs & pairs);
signals:

public slots:
};
#define SampleDbInstance Singleton<SamplesDb>::instance()
#endif // SAMPLESDB_H
