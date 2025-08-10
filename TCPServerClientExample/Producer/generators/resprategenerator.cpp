#include "resprategenerator.h"
#include <QRandomGenerator>
RespRateGenerator::RespRateGenerator()
    : IDataGenerator(MessageType::RespiratoryRate, "Respiratory Rate",
                     "breaths/min", 12, 20),
      m_currentValue(16.0) {}

const qreal &RespRateGenerator::generateData() {
  // Add small variation to simulate natural breathing rate changes
  qreal noise =
      (QRandomGenerator::global()->bounded(0.4) - 0.2); // ±0.2 variation
  m_currentValue += noise;

  // Clamp to normal range
  if (m_currentValue < minValue)
    m_currentValue = minValue;
  if (m_currentValue > maxValue)
    m_currentValue = maxValue;

  return m_currentValue;
}
