#ifndef DIALINDICATOR_H
#define DIALINDICATOR_H

#include <QColor>
#include <QQuickPaintedItem>
#include <QString>

class DialIndicator : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(
      QString parmName READ parmName WRITE setParmName NOTIFY parmNameChanged)
  Q_PROPERTY(QString units READ units WRITE setUnits NOTIFY unitsChanged)
  Q_PROPERTY(
      double minValue READ minValue WRITE setMinValue NOTIFY minValueChanged)
  Q_PROPERTY(
      double maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
  Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
  Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE
                 setBackgroundColor NOTIFY backgroundColorChanged)
  Q_PROPERTY(QColor dialBgColor READ dialBgColor WRITE setDialBgColor NOTIFY
                 dialBgColorChanged)
  Q_PROPERTY(QColor progressColor READ progressColor WRITE setProgressColor
                 NOTIFY progressColorChanged)
  Q_PROPERTY(QColor needleColor READ needleColor WRITE setNeedleColor NOTIFY
                 needleColorChanged)
  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY
                 textColorChanged)
  Q_PROPERTY(
      int thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
  Q_PROPERTY(int cornerRadius READ cornerRadius WRITE setCornerRadius NOTIFY
                 cornerRadiusChanged)

public:
  explicit DialIndicator(QQuickItem *parent = nullptr);

  QString parmName() const { return m_parmName; }
  void setParmName(const QString &name);

  QString units() const { return m_units; }
  void setUnits(const QString &u);

  double minValue() const { return m_minValue; }
  void setMinValue(double val);

  double maxValue() const { return m_maxValue; }
  void setMaxValue(double val);

  double value() const { return m_value; }
  void setValue(double val);

  QColor backgroundColor() const { return m_backgroundColor; }
  void setBackgroundColor(const QColor &color);

  QColor dialBgColor() const { return m_dialBgColor; }
  void setDialBgColor(const QColor &color);

  QColor progressColor() const { return m_progressColor; }
  void setProgressColor(const QColor &color);

  QColor needleColor() const { return m_needleColor; }
  void setNeedleColor(const QColor &color);

  QColor textColor() const { return m_textColor; }
  void setTextColor(const QColor &color);

  int thickness() const { return m_thickness; }
  void setThickness(int val);

  int cornerRadius() const { return m_cornerRadius; }
  void setCornerRadius(int val);

  void paint(QPainter *painter) override;

signals:
  void parmNameChanged();
  void unitsChanged();
  void minValueChanged();
  void maxValueChanged();
  void valueChanged();
  void backgroundColorChanged();
  void dialBgColorChanged();
  void progressColorChanged();
  void needleColorChanged();
  void textColorChanged();
  void thicknessChanged();
  void cornerRadiusChanged();

private:
  QString m_parmName = "Heart Rate";
  QString m_units = "BPM";
  double m_minValue = 40;
  double m_maxValue = 150;
  double m_value = 77;
  QColor m_backgroundColor = QColor("#0f2430");
  QColor m_dialBgColor = QColor("#2f3a44");
  QColor m_progressColor = QColor("#ff6b6b");
  QColor m_needleColor = QColor("#ff2e6f");
  QColor m_textColor = QColor("#ffffff");
  int m_thickness = 12;
  int m_cornerRadius = 8;
};

#endif // DIALINDICATOR_H
