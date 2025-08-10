#include "nibpsystolicgenerator.h"

NIBPSystolicGenerator::NIBPSystolicGenerator()
    : IDataGenerator(MessageType::NIBPSystole, "NIBP Systolic", "mmHg", 90,
                     140),
      m_currentValue(120.0) {}

const qreal &NIBPSystolicGenerator::generateData() {
  // Small random change ±1 mmHg
  qreal noise = (QRandomGenerator::global()->bounded(2.0) - 1.0);
  m_currentValue += noise;

  if (m_currentValue < minValue)
    m_currentValue = minValue;
  if (m_currentValue > maxValue)
    m_currentValue = maxValue;

  return m_currentValue;
}
