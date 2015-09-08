#ifndef DEFINES_H
#define DEFINES_H
#include <QVector>
#include <QPair>
typedef double DataType;
typedef QVector<DataType> QDataVector;
typedef std::vector<DataType> DataVector;
typedef std::vector<DataVector> DataVectors;
typedef double TransformedSample;
typedef std::vector< TransformedSample > TransformedVector;
typedef std::vector<TransformedVector> TransformedVectors;
typedef std::vector<TransformedSample> FilteredFrame;
typedef std::vector<FilteredFrame> FilteredFrames;
typedef QPair<QString, FilteredFrames> CoefficientsResult;
typedef QVector<CoefficientsResult> CoefficientsResults;
#endif // DEFINES_H

