#ifndef COMMONMESSAGES_H
#define COMMONMESSAGES_H

#include "qobjectdefs.h"
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaEnum>
#include <QString>
#include <QtEndian>
#include <QtGlobal>

namespace CommonMessages {
Q_NAMESPACE
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
Q_ENUM_NS(MessageType)
inline constexpr int CURRENT_VERSION = 1;
inline constexpr char SECRET_KEY[] = "Blue$Tundra7!Falcon^Rise";
namespace CommonKeys {
inline constexpr char PARAMETER_TYPE[] = "parameterType";
inline constexpr char PARAM_NAME[] = "paramName";
inline constexpr char VALUE[] = "value";
inline constexpr char UNITS[] = "units";
inline constexpr char VERSION[] = "version";
} // namespace CommonKeys
// Enum to string conversion
inline QString parameterTypeToString(MessageType type) {
  return QString(
      QMetaEnum::fromType<MessageType>().valueToKey(static_cast<int>(type)));
}

// String to enum conversion, returns bool for success
inline bool stringToParameterType(const QString &str, MessageType &outType) {
  int value =
      QMetaEnum::fromType<MessageType>().keyToValue(str.toUtf8().constData());
  if (value == -1) {
    return false; // conversion failed
  }
  outType = static_cast<MessageType>(value);
  return true; // success
}

inline QByteArray frameMessage(const QJsonObject &jsonObj) {
  QJsonDocument doc(jsonObj);
  QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

  QByteArray framedMessage;
  quint32 len = jsonData.size();
  quint32 beLen = qToBigEndian(len);
  framedMessage.append(reinterpret_cast<const char *>(&beLen), sizeof(beLen));
  framedMessage.append(jsonData);

  return framedMessage;
}

inline bool deframeMessage(QByteArray &buffer, QJsonObject &jsonObj) {
  const int headerSize = sizeof(quint32);
  if (buffer.size() < headerSize)
    return false;

  quint32 beLen;
  memcpy(&beLen, buffer.constData(), headerSize);
  quint32 msgLen = qFromBigEndian(beLen);

  if (buffer.size() < headerSize + (int)msgLen)
    return false;

  QByteArray jsonData = buffer.mid(headerSize, msgLen);
  QJsonParseError parseError;
  QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

  if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
    buffer.clear();
    return false;
  }

  jsonObj = doc.object();
  buffer.remove(0, headerSize + msgLen);
  return true;
}

inline bool validateMessage(const QJsonObject &obj) {
  return obj.contains(CommonKeys::PARAMETER_TYPE) &&
         obj.contains(CommonKeys::PARAM_NAME) &&
         obj.contains(CommonKeys::VALUE) && obj.contains(CommonKeys::UNITS) &&
         obj.contains(CommonKeys::VERSION) &&
         obj[CommonKeys::VERSION].toInt() == CURRENT_VERSION;
}

} // namespace CommonMessages
#endif // COMMONMESSAGES_H
