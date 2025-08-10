#include "nibpdata.h"
#include <QtGlobal> // for qFuzzyCompare

NIBPData::NIBPData(QObject *parent)
    : QObject(parent), m_paramName("NIBP"), m_sysValue(118.9), m_diaValue(80.8),
      m_sysMin(40), m_sysMax(180), m_diaMin(40), m_diaMax(120),
      m_units("mmHg") {}

QString NIBPData::paramName() const { return m_paramName; }

void NIBPData::setParamName(const QString &val) {
  if (val != m_paramName) {
    m_paramName = val;
    emit paramNameChanged();
  }
}

double NIBPData::sysValue() const { return m_sysValue; }

void NIBPData::setSysValue(double val) {
  if (!qFuzzyCompare(val + 1, m_sysValue + 1)) {
    m_sysValue = val;
    emit sysValueChanged();
  }
}

double NIBPData::diaValue() const { return m_diaValue; }

void NIBPData::setDiaValue(double val) {
  if (!qFuzzyCompare(val + 1, m_diaValue + 1)) {
    m_diaValue = val;
    emit diaValueChanged();
  }
}

double NIBPData::sysMin() const { return m_sysMin; }

void NIBPData::setSysMin(double val) {
  if (!qFuzzyCompare(val + 1, m_sysMin + 1)) {
    m_sysMin = val;
    emit sysMinChanged();
  }
}

double NIBPData::sysMax() const { return m_sysMax; }

void NIBPData::setSysMax(double val) {
  if (!qFuzzyCompare(val + 1, m_sysMax + 1)) {
    m_sysMax = val;
    emit sysMaxChanged();
  }
}

double NIBPData::diaMin() const { return m_diaMin; }

void NIBPData::setDiaMin(double val) {
  if (!qFuzzyCompare(val + 1, m_diaMin + 1)) {
    m_diaMin = val;
    emit diaMinChanged();
  }
}

double NIBPData::diaMax() const { return m_diaMax; }

void NIBPData::setDiaMax(double val) {
  if (!qFuzzyCompare(val + 1, m_diaMax + 1)) {
    m_diaMax = val;
    emit diaMaxChanged();
  }
}

QString NIBPData::units() const { return m_units; }

void NIBPData::setUnits(const QString &val) {
  if (val != m_units) {
    m_units = val;
    emit unitsChanged();
  }
}
