#ifndef DEFINES_H
#define DEFINES_H
#include <QVector>
#include <QPair>
#include <QString>
typedef double DataType;
typedef QVector<DataType> QDataVector;
typedef std::vector<DataType> DataVector;
typedef std::vector<DataVector> DataVectors;
typedef double TransformedSample;
typedef std::vector< TransformedSample > TransformedVector;
typedef std::vector<TransformedVector> TransformedVectors;
typedef QVector<TransformedSample> FilteredFrame;
typedef QVector<FilteredFrame> FilteredFrames;
typedef QPair<QString, FilteredFrames> CoefficientsResult;
typedef QVector<CoefficientsResult> CoefficientsResults;
typedef QPair<QString, double> DistancePair;
typedef QVector<DistancePair> DistancePairs;
#endif // DEFINES_H

