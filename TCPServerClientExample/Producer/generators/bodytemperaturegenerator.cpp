#include "bodytemperaturegenerator.h"

BodyTemperatureGenerator::BodyTemperatureGenerator()
    : IDataGenerator(MessageType::BodyTemp, "Body Temperature", "°C", 35, 42),
      m_currentValue(37.0) {}

const qreal &BodyTemperatureGenerator::generateData() {
  // Tiny fluctuation ±0.05 °C
  qreal noise = (QRandomGenerator::global()->bounded(0.1) - 0.05);
  m_currentValue += noise;

  // Clamp to normal range
  if (m_currentValue < minValue)
    m_currentValue = minValue;
  if (m_currentValue > maxValue)
    m_currentValue = maxValue;

  return m_currentValue;
}
