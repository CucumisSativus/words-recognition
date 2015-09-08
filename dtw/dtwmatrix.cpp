#include "dtwmatrix.h"

DtwMatrix::DtwMatrix(const CoefficientsResult &fromDb, const CoefficientsResult &recorded)
  : fromDb(fromDb),
    recorded(recorded),
    matrix(fromDb.second.size(), recorded.second.size(), std::numeric_limits<double>::infinity())
{
  matrix.set(0,0,0);
}

