#ifndef DEFINES_H
#define DEFINES_H
#include <QVector>
typedef double DataType;
typedef QVector<DataType> QDataVector;
typedef std::vector<DataType> DataVector;
typedef std::vector<DataVector> DataVectors;
typedef double TransformedSample;
typedef std::vector< TransformedSample > TransformedVector;
typedef std::vector<TransformedVector> TransformedVectors;
typedef std::vector<TransformedSample> FilteredFrame;
#endif // DEFINES_H

