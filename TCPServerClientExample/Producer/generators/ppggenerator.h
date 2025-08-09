#ifndef PPGGENERATOR_H
#define PPGGENERATOR_H
#include "idatagenerator.h"

class PPGGenerator : public IDataGenerator {
public:
  PPGGenerator();
  virtual ~PPGGenerator() = default;
  virtual const qreal &generateData() override;

private:
  qreal m_lastValue;
  qreal m_phase;
};

#endif // PPGGENERATOR_H
