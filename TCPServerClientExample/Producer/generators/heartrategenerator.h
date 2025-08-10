#ifndef HEARTRATEGENERATOR_H
#define HEARTRATEGENERATOR_H
#include "idatagenerator.h"

class HeartRateGenerator : public IDataGenerator {
public:
  HeartRateGenerator();
  virtual ~HeartRateGenerator() = default;
  virtual const qreal &generateData() override;

private:
  qreal m_currentValue;
};

#endif // HEARTRATEGENERATOR_H
