#include "dialindicator.h"
#include <QPainter>
#include <QtMath>

DialIndicator::DialIndicator(QQuickItem *parent) : QQuickPaintedItem(parent) {
  setAntialiasing(true);
}

// Setters (all same pattern)
void DialIndicator::setParmName(const QString &name) {
  if (m_parmName != name) {
    m_parmName = name;
    emit parmNameChanged();
    update();
  }
}
void DialIndicator::setUnits(const QString &u) {
  if (m_units != u) {
    m_units = u;
    emit unitsChanged();
    update();
  }
}
void DialIndicator::setMinValue(double val) {
  if (!qFuzzyCompare(m_minValue, val)) {
    m_minValue = val;
    emit minValueChanged();
    update();
  }
}
void DialIndicator::setMaxValue(double val) {
  if (!qFuzzyCompare(m_maxValue, val)) {
    m_maxValue = val;
    emit maxValueChanged();
    update();
  }
}
void DialIndicator::setValue(double val) {
  if (!qFuzzyCompare(m_value, val)) {
    m_value = val;
    emit valueChanged();
    update();
  }
}
void DialIndicator::setBackgroundColor(const QColor &c) {
  if (m_backgroundColor != c) {
    m_backgroundColor = c;
    emit backgroundColorChanged();
    update();
  }
}
void DialIndicator::setDialBgColor(const QColor &c) {
  if (m_dialBgColor != c) {
    m_dialBgColor = c;
    emit dialBgColorChanged();
    update();
  }
}
void DialIndicator::setProgressColor(const QColor &c) {
  if (m_progressColor != c) {
    m_progressColor = c;
    emit progressColorChanged();
    update();
  }
}
void DialIndicator::setNeedleColor(const QColor &c) {
  if (m_needleColor != c) {
    m_needleColor = c;
    emit needleColorChanged();
    update();
  }
}
void DialIndicator::setTextColor(const QColor &c) {
  if (m_textColor != c) {
    m_textColor = c;
    emit textColorChanged();
    update();
  }
}
void DialIndicator::setThickness(int val) {
  if (m_thickness != val) {
    m_thickness = val;
    emit thicknessChanged();
    update();
  }
}
void DialIndicator::setCornerRadius(int val) {
  if (m_cornerRadius != val) {
    m_cornerRadius = val;
    emit cornerRadiusChanged();
    update();
  }
}

void DialIndicator::paint(QPainter *painter) {
  painter->setRenderHint(QPainter::Antialiasing);

  QRectF rect = boundingRect();

  // Draw background
  painter->setBrush(m_backgroundColor);
  painter->setPen(Qt::NoPen);
  painter->drawRoundedRect(rect, m_cornerRadius, m_cornerRadius);

  // Layout calculation
  QPointF center(rect.center().x(),
                 rect.center().y() - 10); // shift up for labels
  double radius = qMin(rect.width(), rect.height()) / 2 - m_thickness - 10;

  double startAngleDeg = 216;
  double spanAngleDeg = -252;
  double norm =
      qBound(0.0, (m_value - m_minValue) / (m_maxValue - m_minValue), 1.0);

  // Background arc
  QPen penBg(m_dialBgColor, m_thickness, Qt::SolidLine, Qt::RoundCap);
  painter->setPen(penBg);
  painter->drawArc(
      QRectF(center.x() - radius, center.y() - radius, radius * 2, radius * 2),
      startAngleDeg * 16, spanAngleDeg * 16);

  // Progress arc
  QPen penProgress(m_progressColor, m_thickness, Qt::SolidLine, Qt::RoundCap);
  painter->setPen(penProgress);
  painter->drawArc(
      QRectF(center.x() - radius, center.y() - radius, radius * 2, radius * 2),
      startAngleDeg * 16, spanAngleDeg * norm * 16);

  // Needle
  double angleRad = qDegreesToRadians(startAngleDeg + spanAngleDeg * norm);
  QPointF needleEnd(center.x() + radius * qCos(angleRad),
                    center.y() - radius * qSin(angleRad));
  QPen penNeedle(m_needleColor, 3, Qt::SolidLine, Qt::RoundCap);
  painter->setPen(penNeedle);
  painter->drawLine(center, needleEnd);

  // Center cap
  painter->setBrush(Qt::white);
  painter->setPen(Qt::NoPen);
  painter->drawEllipse(center, 5, 5);

  // Parm name (title)
  painter->setPen(m_textColor);
  QFont fontTitle = painter->font();
  fontTitle.setPointSize(10);
  painter->setFont(fontTitle);
  painter->drawText(QRectF(rect.x(), rect.y() + 5, rect.width(), 30),
                    Qt::AlignHCenter, m_parmName);

  // Min label
  painter->setFont(QFont(painter->font().family(), 8));
  painter->drawText(QRectF(rect.x() + 10, center.y() + 35, 30, 15),
                    Qt::AlignLeft | Qt::AlignVCenter,
                    QString::number(m_minValue, 'f', 0));

  // Max label
  painter->drawText(QRectF(rect.right() - 40, center.y() + 35, 30, 15),
                    Qt::AlignRight | Qt::AlignVCenter,
                    QString::number(m_maxValue, 'f', 0));

  // Current value (big)
  QFont fontValue = painter->font();
  fontValue.setPointSize(18);
  fontValue.setBold(true);
  painter->setFont(fontValue);
  painter->drawText(QRectF(rect.x(), rect.bottom() - 60, rect.width(), 40),
                    Qt::AlignHCenter, QString::number(m_value, 'f', 0));

  // Units
  QFont fontUnits = painter->font();
  fontUnits.setPointSize(9);
  fontUnits.setBold(false);
  painter->setFont(fontUnits);
  painter->drawText(QRectF(rect.x(), rect.bottom() - 25, rect.width(), 20),
                    Qt::AlignHCenter, m_units);
}
