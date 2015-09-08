#ifndef SAMPLESDB_H
#define SAMPLESDB_H

#include <QObject>
#include <QVector>
#include "singleton/singleton.h"
#include "../defines.h"

class SamplesDb : public QObject
{
  Q_OBJECT
public:
  explicit SamplesDb(QObject *parent = 0);

  void appendResults(const QString & name, const FilteredFrames & results);
  CoefficientsResults results;
signals:

public slots:
};
#define SampleDbInstance Singleton<SamplesDb>::instance()
#endif // SAMPLESDB_H
