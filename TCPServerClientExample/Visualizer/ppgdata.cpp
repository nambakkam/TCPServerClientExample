#include "PPGData.h"

PPGData::PPGData(QObject *parent)
    : QObject(parent), m_paramName("PPG"), m_value(0.0), m_minValue(0.0),
      m_maxValue(5.0), m_units("AU"), m_frequency(1) // AU = Arbitrary Units, adjust as needed
{}

QString PPGData::paramName() const { return m_paramName; }

void PPGData::setParamName(const QString &val) {
  if (m_paramName != val) {
    m_paramName = val;
    emit paramNameChanged();
  }
}

double PPGData::value() const { return m_value; }

void PPGData::setValue(double val) {
  m_value = val;
  emit valueChanged();
}

double PPGData::minValue() const { return m_minValue; }

void PPGData::setMinValue(double val) {
  if (!qFuzzyCompare(m_minValue, val)) {
    m_minValue = val;
    emit minValueChanged();
  }
}

double PPGData::maxValue() const { return m_maxValue; }

void PPGData::setMaxValue(double val) {
  if (!qFuzzyCompare(m_maxValue, val)) {
    m_maxValue = val;
    emit maxValueChanged();
  }
}

QString PPGData::units() const { return m_units; }

void PPGData::setUnits(const QString &val) {
  if (m_units != val) {
    m_units = val;
    emit unitsChanged();
  }
}


int PPGData::frequency() const
{
    return m_frequency;
}

void PPGData::setFrequency(int val)
{
    if (val != m_frequency) {
        m_frequency = val;
        emit frequencyChanged();
    }
}
