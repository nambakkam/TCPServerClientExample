#ifndef IDATAGENERATOR_H
#define IDATAGENERATOR_H
#include <QObject>

class IDataGenerator {
public:
  explicit IDataGenerator(const QString &paramNameVal = "",
                          const QString &paramUnitsVal = "");
  virtual ~IDataGenerator() = default;
  virtual const qreal &generateData() = 0;
  virtual const QString &getParameterName();
  virtual const QString &getParameterUnits();

protected:
  QString paramName;
  QString paramUnits;
};

#endif // IDATAGENERATOR_H
