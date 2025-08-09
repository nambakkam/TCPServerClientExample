#include "heartrategenerator.h"
#include <QRandomGenerator>
HeartRateGenerator::HeartRateGenerator()
    : IDataGenerator("Heart Rate", "BPM"),
      m_currentValue(75.0), // typical resting value
      m_minRate(60.0), m_maxRate(100.0) {}

const qreal &HeartRateGenerator::generateData() {
  // Add small variation (±1.0 BPM per sample)
  qreal noise =
      (QRandomGenerator::global()->bounded(2.0) - 1.0); // [-1.0, +1.0]
  m_currentValue += noise;

  // Clamp to range
  if (m_currentValue < m_minRate)
    m_currentValue = m_minRate;
  if (m_currentValue > m_maxRate)
    m_currentValue = m_maxRate;

  return m_currentValue;
}
