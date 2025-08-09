#include "etco2generator.h"
#include <QtMath>

EtCO2Generator::EtCO2Generator()
    : IDataGenerator(MessageType::EtCo2, "EtCO2", "mmHg"), m_phase(0.0),
      m_frequency(0.25),  // ~15 breaths/min
      m_samplingRate(50), // smoother waveform
      m_currentValue(0.0) {}

const qreal &EtCO2Generator::generateData() {
  // Step through breath cycle
  m_phase += (2.0 * M_PI * m_frequency) / m_samplingRate;
  if (m_phase > 2.0 * M_PI)
    m_phase -= 2.0 * M_PI;

  // Normalize phase to 0..1
  qreal normPhase = m_phase / (2.0 * M_PI);

  qreal etco2Value = 0.0;

  // Simple 4-phase model for capnogram
  if (normPhase < 0.2) {
    // Inspiration: near 0 mmHg
    etco2Value = 0.0;
  } else if (normPhase < 0.4) {
    // Rapid rise (exhalation start)
    etco2Value = 45.0 * (normPhase - 0.2) / 0.2;
  } else if (normPhase < 0.8) {
    // Plateau
    etco2Value = 45.0;
  } else {
    // Drop back to 0 (start of inspiration)
    etco2Value = 45.0 * (1.0 - (normPhase - 0.8) / 0.2);
  }

  // Add small noise ±1 mmHg
  etco2Value += (QRandomGenerator::global()->bounded(2.0) - 1.0);

  if (etco2Value < 0.0)
    etco2Value = 0.0;
  if (etco2Value > 50.0)
    etco2Value = 50.0;

  m_currentValue = etco2Value;
  return m_currentValue;
}
