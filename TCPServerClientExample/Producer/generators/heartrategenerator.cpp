#include "heartrategenerator.h"
#include <QRandomGenerator>
HeartRateGenerator::HeartRateGenerator()
    : IDataGenerator(MessageType::HeartRate, "Heart Rate", "BPM", 40, 180),
      m_currentValue(75.0) {}

const qreal &HeartRateGenerator::generateData() {
  // Add small variation (±1.0 BPM per sample)
  qreal noise =
      (QRandomGenerator::global()->bounded(2.0) - 1.0); // [-1.0, +1.0]
  m_currentValue += noise;

  // Clamp to range
  if (m_currentValue < minValue)
    m_currentValue = minValue;
  if (m_currentValue > maxValue)
    m_currentValue = maxValue;

  return m_currentValue;
}
