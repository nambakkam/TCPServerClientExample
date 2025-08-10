#ifndef NIBPDATA_H
#define NIBPDATA_H

#include <QObject>

class NIBPData : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString paramName READ paramName WRITE setParamName NOTIFY
                 paramNameChanged)
  Q_PROPERTY(
      double sysValue READ sysValue WRITE setSysValue NOTIFY sysValueChanged)
  Q_PROPERTY(
      double diaValue READ diaValue WRITE setDiaValue NOTIFY diaValueChanged)
  Q_PROPERTY(double sysMin READ sysMin WRITE setSysMin NOTIFY sysMinChanged)
  Q_PROPERTY(double sysMax READ sysMax WRITE setSysMax NOTIFY sysMaxChanged)
  Q_PROPERTY(double diaMin READ diaMin WRITE setDiaMin NOTIFY diaMinChanged)
  Q_PROPERTY(double diaMax READ diaMax WRITE setDiaMax NOTIFY diaMaxChanged)
  Q_PROPERTY(QString units READ units WRITE setUnits NOTIFY unitsChanged)

public:
  explicit NIBPData(QObject *parent = nullptr);

  QString paramName() const;
  void setParamName(const QString &val);

  double sysValue() const;
  void setSysValue(double val);

  double diaValue() const;
  void setDiaValue(double val);

  double sysMin() const;
  void setSysMin(double val);

  double sysMax() const;
  void setSysMax(double val);

  double diaMin() const;
  void setDiaMin(double val);

  double diaMax() const;
  void setDiaMax(double val);

  QString units() const;
  void setUnits(const QString &val);

signals:
  void paramNameChanged();
  void sysValueChanged();
  void diaValueChanged();
  void sysMinChanged();
  void sysMaxChanged();
  void diaMinChanged();
  void diaMaxChanged();
  void unitsChanged();

private:
  QString m_paramName;
  double m_sysValue;
  double m_diaValue;
  double m_sysMin;
  double m_sysMax;
  double m_diaMin;
  double m_diaMax;
  QString m_units;
};

#endif // NIBPDATA_H
