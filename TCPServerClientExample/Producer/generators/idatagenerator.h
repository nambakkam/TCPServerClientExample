#ifndef IDATAGENERATOR_H
#define IDATAGENERATOR_H
#include "commonMessages.h"
#include <QObject>
using namespace CommonMessages;
class IDataGenerator {
public:
  explicit IDataGenerator(const MessageType &paramTypeVal = MessageType::ECG,
                          const QString &paramNameVal = "",
                          const QString &paramUnitsVal = "");
  virtual ~IDataGenerator() = default;
  virtual const qreal &generateData() = 0;
  virtual const MessageType &getParameterType();
  virtual const QString &getParameterName();
  virtual const QString &getParameterUnits();

protected:
  QString paramName;
  QString paramUnits;
  MessageType paramType;
};

#endif // IDATAGENERATOR_H
