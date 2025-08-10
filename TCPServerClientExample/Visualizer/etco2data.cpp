#include "etco2data.h"
#include <QtGlobal>

EtCO2Data::EtCO2Data(QObject *parent)
    : QObject(parent), m_paramName("EtCO2"), m_value(35.0), m_minValue(10.0),
      m_maxValue(50.0), m_units("mmHg"), m_frequency(1) {}

QString EtCO2Data::paramName() const { return m_paramName; }

void EtCO2Data::setParamName(const QString &val) {
  if (val != m_paramName) {
    m_paramName = val;
    emit paramNameChanged();
  }
}

double EtCO2Data::value() const { return m_value; }

void EtCO2Data::setValue(double val) {
  if (!qFuzzyCompare(val + 1, m_value + 1)) {
    m_value = val;
    emit valueChanged();
  }
}

double EtCO2Data::minValue() const { return m_minValue; }

void EtCO2Data::setMinValue(double val) {
  if (!qFuzzyCompare(val + 1, m_minValue + 1)) {
    m_minValue = val;
    emit minValueChanged();
  }
}

double EtCO2Data::maxValue() const { return m_maxValue; }

void EtCO2Data::setMaxValue(double val) {
  if (!qFuzzyCompare(val + 1, m_maxValue + 1)) {
    m_maxValue = val;
    emit maxValueChanged();
  }
}

QString EtCO2Data::units() const { return m_units; }

void EtCO2Data::setUnits(const QString &val) {
  if (val != m_units) {
    m_units = val;
    emit unitsChanged();
  }
}

int EtCO2Data::frequency() const
{
    return m_frequency;
}

void EtCO2Data::setFrequency(const int &val)
{
    if (val != m_frequency) {
        m_frequency = val;
        emit frequencyChanged();
    }
}
