#include "ecgdata.h"

ECGData::ECGData(QObject *parent)
    : QObject(parent), m_paramName("ECG"), m_value(0.0), m_minValue(-1.0),
      m_maxValue(1.0), m_units("mV"), m_frequency(1) {}

QString ECGData::paramName() const { return m_paramName; }

void ECGData::setParamName(const QString &val) {
  if (m_paramName != val) {
    m_paramName = val;
    emit paramNameChanged();
  }
}

double ECGData::value() const { return m_value; }

void ECGData::setValue(double val) {
  m_value = val;
  emit valueChanged();
}

double ECGData::minValue() const { return m_minValue; }

void ECGData::setMinValue(double val) {
  if (!qFuzzyCompare(m_minValue, val)) {
    m_minValue = val;
    emit minValueChanged();
  }
}

double ECGData::maxValue() const { return m_maxValue; }

void ECGData::setMaxValue(double val) {
  if (!qFuzzyCompare(m_maxValue, val)) {
    m_maxValue = val;
    emit maxValueChanged();
  }
}

QString ECGData::units() const { return m_units; }

void ECGData::setUnits(const QString &val) {
  if (m_units != val) {
    m_units = val;
    emit unitsChanged();
  }
}

int ECGData::frequency() const
{
    return m_frequency;

}

void ECGData::setFrequency(const int &val)
{
    if (val != m_frequency) {
        m_frequency = val;
        emit frequencyChanged();
    }
}

