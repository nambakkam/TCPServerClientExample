#ifndef RESPRATEGENERATOR_H
#define RESPRATEGENERATOR_H
#include "idatagenerator.h"

class RespRateGenerator : public IDataGenerator {
public:
  RespRateGenerator();
  virtual ~RespRateGenerator() = default;
  virtual const qreal &generateData() override;

private:
  qreal m_currentValue; // current RR in breaths/min
  qreal m_minRate;      // min possible rate
  qreal m_maxRate;      // max possible rate
};

#endif // RESPRATEGENERATOR_H
