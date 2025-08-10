#include "respwaveformgenerator.h"
#include <QRandomGenerator>
#include <QtMath>
RespWaveFormGenerator::RespWaveFormGenerator()
    : IDataGenerator(MessageType::RespiratoryWaveForm, "Respiratory WaveForm",
                     "L/sec", -2, 2),
      m_phase(0.0), m_frequency(0.25), // 15 breaths/min
      m_samplingRate(50),              // 50 samples/sec
      m_currentValue(0.0) {}

const qreal &RespWaveFormGenerator::generateData() {
  m_phase += (2.0 * M_PI * m_frequency) / m_samplingRate;
  if (m_phase > 2.0 * M_PI)
    m_phase -= 2.0 * M_PI;

  // Sinusoidal breathing airflow
  qreal respValue = 2.0 * qSin(m_phase); // ±2.0 L/sec

  // Add small noise (-0.05 to +0.05)
  respValue += (QRandomGenerator::global()->bounded(0.1) - 0.05);

  m_currentValue = respValue;
  return m_currentValue;
}
