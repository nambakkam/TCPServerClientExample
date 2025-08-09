#ifndef ETCO2GENERATOR_H
#define ETCO2GENERATOR_H

#include "idatagenerator.h"
#include <QRandomGenerator>

class EtCO2Generator : public IDataGenerator {
public:
  EtCO2Generator();
  virtual ~EtCO2Generator() = default;
  virtual const qreal &generateData() override;

private:
  qreal m_phase;
  qreal m_frequency;    // breaths per second
  qreal m_samplingRate; // samples per second
  qreal m_currentValue;
};

#endif // ETCO2GENERATOR_H
