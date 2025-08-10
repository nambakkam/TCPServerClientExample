#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "ecgdata.h"
#include "etco2data.h"
#include "nibpdata.h"
#include "parametermodel.h"
#include "ppgdata.h"
#include "respwaveformdata.h"
#include "temperaturedata.h"
#include <QJsonObject>
#include <QObject>
class DataHandler : public QObject {
  Q_OBJECT
  Q_PROPERTY(ParameterModel *model READ getModel CONSTANT)
  Q_PROPERTY(NIBPData *nibp READ nibp CONSTANT)
  Q_PROPERTY(TemperatureData *temperature READ temperature CONSTANT)
  Q_PROPERTY(EtCO2Data *etco2 READ etco2 CONSTANT)
  Q_PROPERTY(ECGData *ecg READ ecg CONSTANT)
  Q_PROPERTY(PPGData *ppg READ ppg CONSTANT)
  Q_PROPERTY(RespWaveformData *respWaveForm READ respWaveForm CONSTANT)
public:
  explicit DataHandler(QObject *parent = nullptr);

  ParameterModel *getModel() { return &model; }
  NIBPData *nibp() { return &nibpData; }
  TemperatureData *temperature() { return &tempData; }
  EtCO2Data *etco2() { return &etco2Data; }
  ECGData *ecg() { return &ecgData; }
  PPGData *ppg() { return &ppgData; }
  RespWaveformData *respWaveForm() { return &respWaveFormData; }
signals:

public slots:
  void onJsonDataReceived(QJsonObject obj);
private slots:
  void setData(const QJsonObject &obj);

private:
  ParameterModel model;
  NIBPData nibpData;
  TemperatureData tempData;
  EtCO2Data etco2Data;
  ECGData ecgData;
  PPGData ppgData;
  RespWaveformData respWaveFormData;
};

#endif // DATAHANDLER_H
