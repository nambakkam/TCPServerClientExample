#ifndef NIBPSYSTOLICGENERATOR_H
#define NIBPSYSTOLICGENERATOR_H

#include "idatagenerator.h"
#include <QRandomGenerator>

class NIBPSystolicGenerator : public IDataGenerator {
public:
  NIBPSystolicGenerator();
  virtual ~NIBPSystolicGenerator() = default;
  virtual const qreal &generateData() override;

private:
  qreal m_currentValue;
  qreal m_minValue;
  qreal m_maxValue;
};

#endif // NIBPSYSTOLICGENERATOR_H
