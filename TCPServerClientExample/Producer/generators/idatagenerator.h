#ifndef IDATAGENERATOR_H
#define IDATAGENERATOR_H
#include "commonMessages.h"
#include <QObject>
using namespace CommonMessages;
class IDataGenerator {
public:
  explicit IDataGenerator(const MessageType &paramTypeVal = MessageType::ECG,
                          const QString &paramNameVal = "",
                          const QString &paramUnitsVal = "",
                          const qreal &minVal = 0, const qreal &maxVal = 0);
  virtual ~IDataGenerator() = default;
  virtual const qreal &generateData() = 0;
  virtual const MessageType &getParameterType();
  virtual const QString &getParameterName();
  virtual const QString &getParameterUnits();
  virtual const qreal &getParameterMinValue();
  virtual const qreal &getParameterMaxValue();

protected:
  QString paramName;
  QString paramUnits;
  MessageType paramType;
  qreal minValue;
  qreal maxValue;
};

#endif // IDATAGENERATOR_H
