#ifndef NIBPDIASTOLICGENERATOR_H
#define NIBPDIASTOLICGENERATOR_H

#include "idatagenerator.h"
#include <QRandomGenerator>

class NIBPDiastolicGenerator : public IDataGenerator {
public:
  NIBPDiastolicGenerator();
  virtual ~NIBPDiastolicGenerator() = default;
  virtual const qreal &generateData() override;

private:
  qreal m_currentValue;
};

#endif // NIBPDIASTOLICGENERATOR_H
