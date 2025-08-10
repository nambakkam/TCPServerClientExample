#include "spo2generator.h"

Spo2Generator::Spo2Generator()
    : IDataGenerator(MessageType::Spo2, "SpO2", "%", 80, 100),
      m_currentValue(98.0) {}

const qreal &Spo2Generator::generateData() {
  // Small random variation ±0.2%
  qreal noise = (QRandomGenerator::global()->bounded(0.4) - 0.2);
  m_currentValue += noise;

  // Clamp to normal range
  if (m_currentValue < minValue)
    m_currentValue = minValue;
  if (m_currentValue > maxValue)
    m_currentValue = maxValue;

  return m_currentValue;
}
