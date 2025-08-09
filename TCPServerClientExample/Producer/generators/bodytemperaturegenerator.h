#ifndef BODYTEMPERATUREGENERATOR_H
#define BODYTEMPERATUREGENERATOR_H

#include "idatagenerator.h"
#include <QRandomGenerator>

class BodyTemperatureGenerator : public IDataGenerator {
public:
  BodyTemperatureGenerator();
  virtual ~BodyTemperatureGenerator() = default;
  virtual const qreal &generateData() override;

private:
  qreal m_currentValue;
  qreal m_minValue;
  qreal m_maxValue;
};

#endif // BODYTEMPERATUREGENERATOR_H
