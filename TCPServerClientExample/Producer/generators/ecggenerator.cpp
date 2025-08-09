#include "ecggenerator.h"
#include <QRandomGenerator>
#include <QtMath>
ECGGenerator::ECGGenerator()
    : IDataGenerator("ECG", "mV"), m_phase(0.0), m_samplingRate(500),
      m_frequency(1.0), m_currentValue(0) {}

const qreal &ECGGenerator::generateData() {
  // Step forward in the waveform
  m_phase += (2.0 * M_PI * m_frequency) / m_samplingRate;
  if (m_phase > 2.0 * M_PI)
    m_phase -= 2.0 * M_PI;

  // Generate a pseudo ECG waveform
  // Combination of sine + some sharper peaks
  qreal ecgValue =
      0.1 * qSin(m_phase) +                                // small baseline
      1.5 * qExp(-qPow((m_phase - M_PI / 4) * 15, 2)) +    // QRS spike
      0.5 * qExp(-qPow((m_phase - 3 * M_PI / 4) * 5, 2)) + // T wave
      QRandomGenerator::global()->bounded(0.1) - 0.05;     // noise

  m_currentValue = ecgValue;
  return m_currentValue;
}
