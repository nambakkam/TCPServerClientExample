#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "etco2data.h"
#include "nibpdata.h"
#include "parametermodel.h"
#include "temperaturedata.h"
#include <QJsonObject>
#include <QObject>
class DataHandler : public QObject {
  Q_OBJECT
  Q_PROPERTY(ParameterModel *model READ getModel CONSTANT)
  Q_PROPERTY(NIBPData *nibp READ nibp CONSTANT)
  Q_PROPERTY(TemperatureData *temperature READ temperature CONSTANT)
  Q_PROPERTY(EtCO2Data *etco2 READ etco2 CONSTANT)
public:
  explicit DataHandler(QObject *parent = nullptr);

  ParameterModel *getModel() { return &model; }
  NIBPData *nibp() { return &nibpData; }
  TemperatureData *temperature() { return &tempData; }
  EtCO2Data *etco2() { return &etco2Data; }

signals:

public slots:
  void onJsonDataReceived(QJsonObject obj);

private:
  ParameterModel model;
  NIBPData nibpData;
  TemperatureData tempData;
  EtCO2Data etco2Data;
};

#endif // DATAHANDLER_H
