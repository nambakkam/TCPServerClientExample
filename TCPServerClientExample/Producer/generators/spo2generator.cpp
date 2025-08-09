#include "spo2generator.h"

Spo2Generator::Spo2Generator()
    : IDataGenerator(MessageType::Spo2, "SpO2", "%"),
      m_currentValue(98.0), // typical resting saturation
      m_minValue(95.0), m_maxValue(100.0) {}

const qreal &Spo2Generator::generateData() {
  // Small random variation ±0.2%
  qreal noise = (QRandomGenerator::global()->bounded(0.4) - 0.2);
  m_currentValue += noise;

  // Clamp to normal range
  if (m_currentValue < m_minValue)
    m_currentValue = m_minValue;
  if (m_currentValue > m_maxValue)
    m_currentValue = m_maxValue;

  return m_currentValue;
}
