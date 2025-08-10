#include "datahandler.h"
#include "commonMessages.h"
using namespace CommonMessages;
DataHandler::DataHandler(QObject *parent) : QObject{parent} {}

void DataHandler::onJsonDataReceived(QJsonObject obj) {
  qDebug() << "JSON Received: " << obj;

  if (!obj.contains(CommonKeys::PARAMETER_TYPE))
    return;

  QString typeStr = obj.value(CommonKeys::PARAMETER_TYPE).toString();
  qDebug() << "Param Type is " << typeStr;
  CommonMessages::MessageType type{MessageType::ECG};
  if (!stringToParameterType(typeStr, type)) {
    qDebug() << "Invalid type" << typeStr;
  }
  qDebug() << "MessageType is " << parameterTypeToString(type);

  double value = obj.value(CommonKeys::VALUE).toDouble();
  double minValue = obj.value(CommonKeys::MINVAL).toDouble();
  double maxValue = obj.value(CommonKeys::MAXVAL).toDouble();
  QString name = obj.value(CommonKeys::PARAM_NAME).toString();
  QString units = obj.value(CommonKeys::UNITS).toString();

  switch (type) {
  case MessageType::NIBPSystole:
    nibpData.setSysMin(minValue);
    nibpData.setSysMax(maxValue);
    nibpData.setParamName(name);
    nibpData.setUnits(units);
    nibpData.setSysValue(value);
    break;
  case MessageType::NIBPDiastole:
    nibpData.setDiaMin(minValue);
    nibpData.setDiaMax(maxValue);
    nibpData.setParamName(name);
    nibpData.setUnits(units);
    nibpData.setDiaValue(value);
    break;
  case MessageType::BodyTemp:
    tempData.setMinValue(minValue);
    tempData.setMaxValue(maxValue);
    tempData.setParamName(name);
    tempData.setUnits(units);
    tempData.setValue(value);
    break;
  case MessageType::EtCo2:
    etco2Data.setMinValue(minValue);
    etco2Data.setMaxValue(maxValue);
    etco2Data.setValue(value);
    etco2Data.setParamName(name);
    etco2Data.setUnits(units);
    break;
  case MessageType::Spo2:
  case MessageType::HeartRate:
  case MessageType::RespiratoryRate:
    model.updateFromJson(obj);
    break;
  default:
    break;
  }
}
