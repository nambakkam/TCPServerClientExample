#ifndef COMMONMESSAGES_H
#define COMMONMESSAGES_H

#include <QByteArray>
#include <QString>

enum class MessageType {
  ECG,
  PPG,
  RespiratoryWaveForm,
  RespiratoryRate,
  HeartRate,
  Spo2,
  NIBPSystole,
  NIBPDiastole,
  BodyTemp,
  EtCo2
};

struct Message {
  MessageType type;
  QByteArray payload;
};
#endif // COMMONMESSAGES_H
