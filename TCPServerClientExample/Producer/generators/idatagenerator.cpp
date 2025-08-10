#include "idatagenerator.h"

IDataGenerator::IDataGenerator(const MessageType &paramTypeVal,
                               const QString &paramNameVal,
                               const QString &paramUnitsVal,
                               const qreal &minVal, const qreal &maxVal)
    : paramName{paramNameVal}, paramUnits{paramUnitsVal},
      paramType{paramTypeVal}, minValue{minVal}, maxValue{maxVal} {}

const MessageType &IDataGenerator::getParameterType() { return paramType; }

const QString &IDataGenerator::getParameterName() { return paramName; }

const QString &IDataGenerator::getParameterUnits() { return paramUnits; }

const qreal &IDataGenerator::getParameterMinValue() { return minValue; }

const qreal &IDataGenerator::getParameterMaxValue() { return maxValue; }
