#include "idatagenerator.h"

IDataGenerator::IDataGenerator(const MessageType &paramTypeVal,
                               const QString &paramNameVal,
                               const QString &paramUnitsVal)
    : paramName{paramNameVal}, paramUnits{paramUnitsVal},
      paramType{paramTypeVal} {}

const MessageType &IDataGenerator::getParameterType() { return paramType; }

const QString &IDataGenerator::getParameterName() { return paramName; }

const QString &IDataGenerator::getParameterUnits() { return paramUnits; }
