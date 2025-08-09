#ifndef ECGGENERATOR_H
#define ECGGENERATOR_H
#include "idatagenerator.h"
class ECGGenerator : public IDataGenerator {
public:
  ECGGenerator();
  virtual ~ECGGenerator() = default;
  virtual const qreal &generateData() override;

private:
  qreal m_phase;
  qreal m_samplingRate;
  qreal m_frequency;
  qreal m_currentValue;
};

#endif // ECGGENERATOR_H
