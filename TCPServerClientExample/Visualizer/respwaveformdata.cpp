#include "respwaveformdata.h"

RespWaveformData::RespWaveformData(QObject *parent)
    : QObject(parent), m_paramName("Resp Waveform"), m_value(0.0),
      m_minValue(0.0), m_maxValue(5.0),
      m_units("AU"), m_frequency(1) // AU = Arbitrary Units, change if you have specific units
{}

QString RespWaveformData::paramName() const { return m_paramName; }

void RespWaveformData::setParamName(const QString &val) {
  if (m_paramName != val) {
    m_paramName = val;
    emit paramNameChanged();
  }
}

double RespWaveformData::value() const { return m_value; }

void RespWaveformData::setValue(double val) {
  m_value = val;
  emit valueChanged();
}

double RespWaveformData::minValue() const { return m_minValue; }

void RespWaveformData::setMinValue(double val) {
  if (!qFuzzyCompare(m_minValue, val)) {
    m_minValue = val;
    emit minValueChanged();
  }
}

double RespWaveformData::maxValue() const { return m_maxValue; }

void RespWaveformData::setMaxValue(double val) {
  if (!qFuzzyCompare(m_maxValue, val)) {
    m_maxValue = val;
    emit maxValueChanged();
  }
}

QString RespWaveformData::units() const { return m_units; }

void RespWaveformData::setUnits(const QString &val) {
  if (m_units != val) {
    m_units = val;
    emit unitsChanged();
  }
}

int RespWaveformData::frequency() const
{
    return m_frequency;
}

void RespWaveformData::setFrequency(int val)
{
    if (val != m_frequency) {
        m_frequency = val;
        emit frequencyChanged();
    }
}
