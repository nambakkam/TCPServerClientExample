#include "nibpdiastolicgenerator.h"

NIBPDiastolicGenerator::NIBPDiastolicGenerator()
    : IDataGenerator("NIBP Diastolic", "mmHg"), m_currentValue(80.0),
      m_minValue(60.0), m_maxValue(90.0) {}

const qreal &NIBPDiastolicGenerator::generateData() {
  // Small random change ±1 mmHg
  qreal noise = (QRandomGenerator::global()->bounded(2.0) - 1.0);
  m_currentValue += noise;

  if (m_currentValue < m_minValue)
    m_currentValue = m_minValue;
  if (m_currentValue > m_maxValue)
    m_currentValue = m_maxValue;

  return m_currentValue;
}
