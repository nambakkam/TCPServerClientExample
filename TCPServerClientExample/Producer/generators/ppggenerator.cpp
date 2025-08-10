#include "ppggenerator.h"
#include <QRandomGenerator>
#include <QtMath>
PPGGenerator::PPGGenerator()
    : IDataGenerator(MessageType::PPG, "PPG", "", 0, 1), m_lastValue(0.5),
      m_phase(0) {}

const qreal &PPGGenerator::generateData() {
  m_phase += 0.1;
  if (m_phase > 2 * M_PI)
    m_phase -= 2 * M_PI;
  qreal noise = (QRandomGenerator::global()->generateDouble() * 0.02) - 0.01;
  m_lastValue = 0.6 + 0.2 * qSin(m_phase) + noise;

  // Clamp to realistic range
  if (m_lastValue < 0.4)
    m_lastValue = 0.4;
  if (m_lastValue > 0.8)
    m_lastValue = 0.8;

  return m_lastValue;
}
