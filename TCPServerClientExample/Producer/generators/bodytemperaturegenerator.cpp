#include "bodytemperaturegenerator.h"

BodyTemperatureGenerator::BodyTemperatureGenerator()
    : IDataGenerator(MessageType::BodyTemp, "Body Temperature", "°C"),
      m_currentValue(37.0), m_minValue(36.5), m_maxValue(37.5) {}

const qreal &BodyTemperatureGenerator::generateData() {
  // Tiny fluctuation ±0.05 °C
  qreal noise = (QRandomGenerator::global()->bounded(0.1) - 0.05);
  m_currentValue += noise;

  // Clamp to normal range
  if (m_currentValue < m_minValue)
    m_currentValue = m_minValue;
  if (m_currentValue > m_maxValue)
    m_currentValue = m_maxValue;

  return m_currentValue;
}
