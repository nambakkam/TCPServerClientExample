#include "temperaturedata.h"
#include <QtGlobal>

TemperatureData::TemperatureData(QObject *parent)
    : QObject(parent), m_paramName("Temperature"), m_value(36.5),
      m_minValue(30.0), m_maxValue(45.0), m_units("°C"), m_frequency(1) {}

QString TemperatureData::paramName() const { return m_paramName; }

void TemperatureData::setParamName(const QString &val) {
  if (val != m_paramName) {
    m_paramName = val;
    emit paramNameChanged();
  }
}

double TemperatureData::value() const { return m_value; }

void TemperatureData::setValue(double val) {
  if (!qFuzzyCompare(val + 1, m_value + 1)) {
    m_value = val;
    emit valueChanged();
  }
}

double TemperatureData::minValue() const { return m_minValue; }

void TemperatureData::setMinValue(double val) {
  if (!qFuzzyCompare(val + 1, m_minValue + 1)) {
    m_minValue = val;
    emit minValueChanged();
  }
}

double TemperatureData::maxValue() const { return m_maxValue; }

void TemperatureData::setMaxValue(double val) {
  if (!qFuzzyCompare(val + 1, m_maxValue + 1)) {
    m_maxValue = val;
    emit maxValueChanged();
  }
}

QString TemperatureData::units() const { return m_units; }

void TemperatureData::setUnits(const QString &val) {
  if (val != m_units) {
    m_units = val;
    emit unitsChanged();
  }
}

int TemperatureData::frequency() const
{
    return m_frequency;
}

void TemperatureData::setFrequency(int val)
{
    if (val != m_frequency) {
        m_frequency = val;
        emit frequencyChanged();
    }
}
