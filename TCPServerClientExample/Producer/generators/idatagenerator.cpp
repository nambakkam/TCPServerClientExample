#include "idatagenerator.h"

IDataGenerator::IDataGenerator(const QString &paramNameVal,
                               const QString &paramUnitsVal)
    : paramName{paramNameVal}, paramUnits{paramUnitsVal} {}

const QString &IDataGenerator::getParameterName() { return paramName; }

const QString &IDataGenerator::getParameterUnits() { return paramUnits; }
