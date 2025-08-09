#include "resprategenerator.h"
#include <QRandomGenerator>
RespRateGenerator::RespRateGenerator()
    : IDataGenerator(MessageType::RespiratoryRate, "Respiratory Rate",
                     "breaths/min"),
      m_currentValue(16.0), // typical resting rate
      m_minRate(12.0), m_maxRate(20.0) {}

const qreal &RespRateGenerator::generateData() {
  // Add small variation to simulate natural breathing rate changes
  qreal noise =
      (QRandomGenerator::global()->bounded(0.4) - 0.2); // ±0.2 variation
  m_currentValue += noise;

  // Clamp to normal range
  if (m_currentValue < m_minRate)
    m_currentValue = m_minRate;
  if (m_currentValue > m_maxRate)
    m_currentValue = m_maxRate;

  return m_currentValue;
}
