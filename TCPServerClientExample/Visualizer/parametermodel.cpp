#include "parametermodel.h"
#include "commonMessages.h"
#include <QDebug>
using namespace CommonMessages;
ParameterModel::ParameterModel(QObject *parent) : QAbstractListModel(parent) {
  m_parameters = {
      {CommonMessages::MessageType::RespiratoryRate, "Respiratory Rate",
       "breaths/min", 0.0, 0.0, 0.0, "#0097e6", "#00a8ff"},
      {CommonMessages::MessageType::HeartRate, "Heart Rate", "BPM", 0.0, 0.0,
       0.0, "#ff2e6f", "#ff6b6b"},
      {CommonMessages::MessageType::Spo2, "Spo2", "%", 0.0, 0.0, 0.0, "#44bd32",
       "#4cd137"},
      // add more if needed
  };
}

int ParameterModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;
  return m_parameters.size();
}

QVariant ParameterModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() < 0 || index.row() >= m_parameters.size())
    return QVariant();

  const ParameterItem &param = m_parameters.at(index.row());

  switch (role) {
  case TypeRole:
    return static_cast<int>(param.type);
  case NameRole:
    return param.name;
  case UnitsRole:
    return param.units;
  case ValueRole:
    return param.value;
  case MinValueRole:
    return param.minValue;
  case MaxValueRole:
    return param.maxValue;
  case NeedleColorRole:
    return param.needleColor;
  case ProgressColorRole:
    return param.progressColor;
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> ParameterModel::roleNames() const {
  return {{TypeRole, "type"},
          {NameRole, "name"},
          {UnitsRole, "units"},
          {ValueRole, "value"},
          {MinValueRole, "minValue"},
          {MaxValueRole, "maxValue"},
          {NeedleColorRole, "needleColor"},
          {ProgressColorRole, "progressColor"}};
}

int ParameterModel::findIndexByType(CommonMessages::MessageType type) const {
  for (int i = 0; i < m_parameters.size(); ++i) {
    if (m_parameters[i].type == type)
      return i;
  }
  return -1;
}

void ParameterModel::updateFromJson(const QJsonObject &obj) {
  /*
   Expected JSON example:
   {
      "parameterType": 9,  // CommonMessages::MessageType::EtCo2
      "paramName": "EtCO₂",
      "value": 36.5,
      "units": "mmHg"
   }
  */
  if (!obj.contains(CommonKeys::PARAMETER_TYPE))
    return;

  QString typeStr = obj.value(CommonKeys::PARAMETER_TYPE).toString();
  CommonMessages::MessageType type{MessageType::ECG};
  if (!stringToParameterType(typeStr, type)) {
    qDebug() << "Invalid type" << typeStr;
  }

  int idx = findIndexByType(type);
  if (idx < 0)
    return; // parameter not found in model

  double value = obj.value(CommonKeys::VALUE).toDouble(m_parameters[idx].value);
  double minValue =
      obj.value(CommonKeys::MINVAL).toDouble(m_parameters[idx].value);
  double maxValue =
      obj.value(CommonKeys::MAXVAL).toDouble(m_parameters[idx].value);
  QString name =
      obj.value(CommonKeys::PARAM_NAME).toString(m_parameters[idx].name);
  QString units =
      obj.value(CommonKeys::UNITS).toString(m_parameters[idx].units);
  bool changed = false;
  if (name != m_parameters[idx].name) {
    m_parameters[idx].name = name;
    changed = true;
  }
  if (units != m_parameters[idx].units) {
    m_parameters[idx].units = units;
    changed = true;
  }
  if (!qFuzzyCompare(m_parameters[idx].value, value)) {
    m_parameters[idx].value = value;
    changed = true;
  }

  if (!qFuzzyCompare(m_parameters[idx].minValue, minValue)) {
    m_parameters[idx].minValue = minValue;
    changed = true;
  }

  if (!qFuzzyCompare(m_parameters[idx].maxValue, maxValue)) {
    m_parameters[idx].maxValue = maxValue;
    changed = true;
  }
  if (changed) {
    QModelIndex modelIndex = index(idx);
    emit dataChanged(
        modelIndex, modelIndex,
        {NameRole, UnitsRole, ValueRole, MinValueRole, MaxValueRole});
  }
}
