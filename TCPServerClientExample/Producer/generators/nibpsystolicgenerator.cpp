#include "nibpsystolicgenerator.h"

NIBPSystolicGenerator::NIBPSystolicGenerator()
    : IDataGenerator("NIBP Systolic", "mmHg"), m_currentValue(120.0),
      m_minValue(100.0), m_maxValue(140.0) {}

const qreal &NIBPSystolicGenerator::generateData() {
  // Small random change ±1 mmHg
  qreal noise = (QRandomGenerator::global()->bounded(2.0) - 1.0);
  m_currentValue += noise;

  if (m_currentValue < m_minValue)
    m_currentValue = m_minValue;
  if (m_currentValue > m_maxValue)
    m_currentValue = m_maxValue;

  return m_currentValue;
}
