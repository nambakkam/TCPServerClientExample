#ifndef SPO2GENERATOR_H
#define SPO2GENERATOR_H

#include "idatagenerator.h"
#include <QRandomGenerator>

class Spo2Generator : public IDataGenerator {
public:
  Spo2Generator();
  virtual ~Spo2Generator() = default;
  virtual const qreal &generateData() override;

private:
  qreal m_currentValue;
  qreal m_minValue;
  qreal m_maxValue;
};

#endif // SPO2GENERATOR_H
