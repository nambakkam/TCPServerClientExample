#ifndef PPGDATA_H
#define PPGDATA_H

#include <QObject>

class PPGData : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString paramName READ paramName WRITE setParamName NOTIFY
                 paramNameChanged)
  Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
  Q_PROPERTY(
      double minValue READ minValue WRITE setMinValue NOTIFY minValueChanged)
  Q_PROPERTY(
      double maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
  Q_PROPERTY(QString units READ units WRITE setUnits NOTIFY unitsChanged)

public:
  explicit PPGData(QObject *parent = nullptr);

  QString paramName() const;
  void setParamName(const QString &val);

  double value() const;
  void setValue(double val);

  double minValue() const;
  void setMinValue(double val);

  double maxValue() const;
  void setMaxValue(double val);

  QString units() const;
  void setUnits(const QString &val);

  int frequency() const;
  void setFrequency(int val);

signals:
  void paramNameChanged();
  void valueChanged();
  void minValueChanged();
  void maxValueChanged();
  void unitsChanged();
  void frequencyChanged();

private:
  QString m_paramName;
  double m_value;
  double m_minValue;
  double m_maxValue;
  QString m_units;
  int m_frequency; // Added frequency property
};

#endif // PPGDATA_H
