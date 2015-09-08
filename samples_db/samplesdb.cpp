#include "samplesdb.h"

SamplesDb::SamplesDb(QObject * parent) : QObject(parent)
{

}

void SamplesDb::appendResults(const QString &name, const FilteredFrames &results)
{
    this->results.push_back(CoefficientsResult(name, results));
}

