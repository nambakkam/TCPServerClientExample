#include "datahandler.h"
#include "commonMessages.h"
#include <QtConcurrent>
using namespace CommonMessages;
DataHandler::DataHandler(QObject *parent) : QObject{parent} {}

void DataHandler::onJsonDataReceived(QJsonObject obj) {
  QtConcurrent::run(this, &DataHandler::setData, obj);
}

void DataHandler::setData(const QJsonObject &obj) {
  if (!obj.contains(CommonKeys::PARAMETER_TYPE))
    return;

  QString typeStr = obj.value(CommonKeys::PARAMETER_TYPE).toString();
  CommonMessages::MessageType type{MessageType::ECG};
  if (!stringToParameterType(typeStr, type)) {
    qDebug() << "Invalid type" << typeStr;
  }

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
    nibpData.setFrequency(ScheduledIntervals::NIBPTime);
    break;
  case MessageType::NIBPDiastole:
    nibpData.setDiaMin(minValue);
    nibpData.setDiaMax(maxValue);
    nibpData.setParamName(name);
    nibpData.setUnits(units);
    nibpData.setDiaValue(value);
    nibpData.setFrequency(ScheduledIntervals::NIBPTime);
    break;
  case MessageType::BodyTemp:
    tempData.setMinValue(minValue);
    tempData.setMaxValue(maxValue);
    tempData.setParamName(name);
    tempData.setUnits(units);
    tempData.setValue(value);
    tempData.setFrequency(ScheduledIntervals::tempTime);
    break;
  case MessageType::EtCo2:
    etco2Data.setMinValue(minValue);
    etco2Data.setMaxValue(maxValue);
    etco2Data.setValue(value);
    etco2Data.setParamName(name);
    etco2Data.setUnits(units);
    etco2Data.setFrequency(ScheduledIntervals::etco2Time);
    break;
  case MessageType::ECG:
    ecgData.setMinValue(minValue);
    ecgData.setMaxValue(maxValue);
    ecgData.setValue(value);
    ecgData.setParamName(name);
    ecgData.setUnits(units);
    ecgData.setFrequency(ScheduledIntervals::ecgTime);
    break;
  case MessageType::PPG:
    ppgData.setMinValue(minValue);
    ppgData.setMaxValue(maxValue);
    ppgData.setValue(value);
    ppgData.setParamName(name);
    ppgData.setUnits(units);
    ppgData.setFrequency(ScheduledIntervals::ppgTime);
    break;
  case MessageType::RespiratoryWaveForm:
    respWaveFormData.setMinValue(minValue);
    respWaveFormData.setMaxValue(maxValue);
    respWaveFormData.setValue(value);
    respWaveFormData.setParamName(name);
    respWaveFormData.setUnits(units);
    respWaveFormData.setFrequency(ScheduledIntervals::respWaveFormTime);
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
