#include "dtwmatrix.h"

DtwMatrix::DtwMatrix(const CoefficientsResult &fromDb, const CoefficientsResult &recorded)
  : fromDb(fromDb),
    recorded(recorded),
    matrix(fromDb.second.size(), recorded.second.size(), std::numeric_limits<double>::infinity()),
    path(fromDb.second.size(), recorded.second.size(), 0)
{
  matrix.set(0,0,0);
  double gmax = 0.0;

  for(unsigned long i=1; i<fromDb.second.size(); ++i){
      for(unsigned long j=1; j<recorded.second.size(); ++j){
          //equation 17
          double cost = dist(fromDb.second[i], recorded.second[j]);
          matrix.set(i,j,
                     (cost +
                      minimum(
                        matrix.get(i-1, j),
                        matrix.get(i,j-1),
                        matrix.get(i-1,j-1)
                        )
                      )
                     );
          if(matrix.get(i,j) > gmax){
              gmax = matrix.get(i,j);
            }
        }
    }
}

GenericGrid<double> DtwMatrix::bestPath(double bandCoefficient)
{
  size_t M = path.numRows();
  size_t N = path.numColumns();
  size_t m = path.numRows() -2;
  size_t n = path.numColumns() -2;

  int w = (int) (N * bandCoefficient);

  while(m != 0 && n != 0){
      path.set(n,m,1);
      double leftCost = matrix.get(m,n-1);
      double upCost = matrix.get(m-1, n);
      double diagCost = matrix.get(m-1, n-1);
      double bestCost = minimum(leftCost, upCost, diagCost);
      if (bestCost == leftCost && std::fabs(n - N/2) < w && n > 0) {
        n--;
      }
      else if (bestCost == upCost && std::fabs(m - M/2) < w && m > 0) {
        m--;
      }
      else {
        m--;
        n--;
      }
    }
  return path;
}

double DtwMatrix::cost(double bandCoefficient)
{
  bestPath(bandCoefficient);
  double cost = 0;
  for(size_t i =0; i< path.numRows(); ++i){
      for(size_t j =0; j< path.numColumns(); ++j){
          double fieldCost = path.get(i,j);
          if(fieldCost != 0){
              cost += fieldCost;
            }
        }
    }
  return cost/(path.numColumns() + path.numRows());
}

double DtwMatrix::dist(const FilteredFrame &mfcc1, const FilteredFrame &mfcc2)
{
  double sum =0.0;
  for(unsigned long i =0; i < mfcc1.size(); ++i){
      sum += std::pow(mfcc1[i] - mfcc2[i], 2);
    }
  return std::sqrt(sum);
}

double DtwMatrix::minimum(double x, double y, double z)
{
  double smallest = std::min(x,y);
  return std::min(smallest, z);
}

