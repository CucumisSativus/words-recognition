#ifndef DTWMATRIX_H
#define DTWMATRIX_H

#include <limits>
#include <cmath>
#include "../defines.h"
#include "genericgrid.h"

class DtwMatrix
{
public:
  DtwMatrix(const CoefficientsResult & fromDb, const CoefficientsResult & recorded);
  GenericGrid<double> bestPath(double bandCoefficient);
  double cost(double bandCoefficient);
private:
  CoefficientsResult fromDb;
  CoefficientsResult recorded;
  GenericGrid<double> matrix;
  GenericGrid<double> path;
  double dist(const FilteredFrame &mfcc1, const FilteredFrame &mfcc2);

  double minimum(double x, double y, double z);
};

#endif // DTWMATRIX_H
