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

signals:

public slots:
};

Singleton<SamplesDb> SamplesDbInstance(){
  return Singleton<SamplesDb>::instance();
}
#endif // SAMPLESDB_H
