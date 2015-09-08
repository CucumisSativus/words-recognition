#ifndef DTWMATRIX_H
#define DTWMATRIX_H

#include <limits>
#include "../defines.h"
#include "genericgrid.h"

class DtwMatrix
{
public:
  DtwMatrix(const CoefficientsResult & fromDb, const CoefficientsResult & recorded);
private:
  CoefficientsResult fromDb;
  CoefficientsResult recorded;
  GenericGrid<double> matrix;
};

#endif // DTWMATRIX_H
