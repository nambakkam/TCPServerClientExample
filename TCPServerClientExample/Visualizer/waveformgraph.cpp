#include "waveformgraph.h"
#include <QFont>
#include <QPainter>
#include <QPen>
#include <algorithm>
#include <chrono>
#include <cmath>

WaveformGraph::WaveformGraph(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_lineColor(Qt::green),
      m_timeWindowSec(20.0) // 30 second window
      ,
      m_minValue(0.0), m_maxValue(1.0), m_updatePending(false),
      m_backgroundDirty(true), m_waveformDirty(true), m_minMaxDirty(true),
      m_frameSkipCounter(0) {
  setAntialiasing(true);
  setFlag(ItemHasContents);

  // Main update timer - reduced frequency for smoother performance
  m_updateTimer = new QTimer(this);
  m_updateTimer->setInterval(UPDATE_INTERVAL_MS);
  m_updateTimer->setSingleShot(true);
  connect(m_updateTimer, &QTimer::timeout, this, &WaveformGraph::onUpdateTimer);

  // Separate cleanup timer to avoid doing cleanup on every data point
  m_cleanupTimer = new QTimer(this);
  m_cleanupTimer->setInterval(CLEANUP_INTERVAL_MS);
  connect(m_cleanupTimer, &QTimer::timeout, this,
          &WaveformGraph::onDataCleanupTimer);
  m_cleanupTimer->start();
}

void WaveformGraph::setParamName(const QString &name) {
  if (m_paramName != name) {
    m_paramName = name;
    m_backgroundDirty = true;
    emit paramNameChanged();
    scheduleUpdate();
  }
}

void WaveformGraph::setUnits(const QString &units) {
  if (m_units != units) {
    m_units = units;
    m_backgroundDirty = true;
    emit unitsChanged();
    scheduleUpdate();
  }
}

void WaveformGraph::setLineColor(const QColor &color) {
  if (m_lineColor != color) {
    m_lineColor = color;
    m_waveformDirty = true;
    emit lineColorChanged();
    scheduleUpdate();
  }
}

void WaveformGraph::setTimeWindowSec(double seconds) {
  if (seconds > 0 && !qFuzzyCompare(m_timeWindowSec, seconds)) {
    m_timeWindowSec = seconds;
    m_backgroundDirty = true;
    m_waveformDirty = true;
    cleanOldData();
    emit timeWindowSecChanged();
    scheduleUpdate();
  }
}

void WaveformGraph::appendValue(double val) {
  auto now = std::chrono::steady_clock::now();

  // Skip frame if data is coming too fast (helps with jitter)
  if (m_lastDataTime.time_since_epoch().count() > 0) {
    auto timeSinceLastData =
        std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                              m_lastDataTime);
    if (timeSinceLastData.count() <
        10) { // Skip if less than 10ms since last data
      m_frameSkipCounter++;
      if (m_frameSkipCounter < 3) { // Only skip a few frames
        return;
      }
    }
  }

  m_frameSkipCounter = 0;
  m_lastDataTime = now;

  m_data.emplace_back(val);
  m_minMaxDirty = true;
  m_waveformDirty = true;

  // Schedule update (won't spam if already pending)
  scheduleUpdate();
}

void WaveformGraph::clear() {
  m_data.clear();
  m_minMaxDirty = true;
  m_waveformDirty = true;
  scheduleUpdate();
}

void WaveformGraph::cleanOldData() {
  if (m_data.empty())
    return;

  auto now = std::chrono::steady_clock::now();
  auto cutoffTime =
      now - std::chrono::milliseconds(static_cast<int>(m_timeWindowSec * 1000));

  size_t originalSize = m_data.size();

  // Remove data points older than the time window
  while (!m_data.empty() && m_data.front().timestamp < cutoffTime) {
    m_data.pop_front();
  }

  if (m_data.size() != originalSize) {
    m_minMaxDirty = true;
    m_waveformDirty = true;
  }
}

void WaveformGraph::scheduleUpdate() {
  if (!m_updatePending) {
    m_updatePending = true;
    m_updateTimer->start();
  }
}

void WaveformGraph::onUpdateTimer() {
  m_updatePending = false;

  if (m_minMaxDirty) {
    updateMinMax();
  }

  update();
}

void WaveformGraph::onDataCleanupTimer() {
  cleanOldData();
  if (m_waveformDirty) {
    scheduleUpdate();
  }
}

void WaveformGraph::updateMinMax() {
  if (m_data.empty()) {
    m_minValue = 0.0;
    m_maxValue = 1.0;
    m_minMaxDirty = false;
    m_backgroundDirty = true; // Y-axis labels need update
    emit minValueChanged();
    emit maxValueChanged();
    return;
  }

  auto minMax = std::minmax_element(
      m_data.begin(), m_data.end(),
      [](const DataPoint &a, const DataPoint &b) { return a.value < b.value; });

  double newMin = minMax.first->value;
  double newMax = minMax.second->value;

  // Add some padding to min/max
  double range = newMax - newMin;
  if (qFuzzyIsNull(range)) {
    newMin -= 0.5;
    newMax += 0.5;
  } else {
    double padding = range * 0.05; // 5% padding
    newMin -= padding;
    newMax += padding;
  }

  bool changed = false;
  if (std::abs(m_minValue - newMin) >
      0.001) { // Use absolute difference instead of qFuzzyCompare
    m_minValue = newMin;
    changed = true;
  }
  if (std::abs(m_maxValue - newMax) > 0.001) {
    m_maxValue = newMax;
    changed = true;
  }

  if (changed) {
    m_backgroundDirty = true; // Y-axis labels need update
    m_waveformDirty = true;
    emit minValueChanged();
    emit maxValueChanged();
  }

  m_minMaxDirty = false;
}

void WaveformGraph::invalidateCache() {
  m_backgroundDirty = true;
  m_waveformDirty = true;
}

void WaveformGraph::geometryChanged(const QRectF &newGeometry,
                                    const QRectF &oldGeometry) {
  QQuickPaintedItem::geometryChanged(newGeometry, oldGeometry);

  QSize newSize = newGeometry.size().toSize();
  if (newSize != m_lastSize) {
    m_lastSize = newSize;
    invalidateCache();
    scheduleUpdate();
  }
}

bool WaveformGraph::shouldUpdateCache() const {
  return m_backgroundDirty || m_waveformDirty ||
         m_cachedBackground.size() != size().toSize() ||
         m_cachedWaveform.size() != size().toSize();
}

void WaveformGraph::renderToCache() {
  QSize widgetSize = size().toSize();
  if (widgetSize.isEmpty())
    return;

  const int marginLeft = 60; // Increased for better Y-axis labels
  const int marginRight = 15;
  const int marginTop = 35;
  const int marginBottom = 35;

  const int fullW = widgetSize.width();
  const int fullH = widgetSize.height();
  const int w = fullW - marginLeft - marginRight;
  const int h = fullH - marginTop - marginBottom;

  if (w <= 0 || h <= 0)
    return;

  // Render background (grid, labels, etc.) - only when needed
  if (m_backgroundDirty || m_cachedBackground.size() != widgetSize) {
    m_cachedBackground = QPixmap(widgetSize);
    m_cachedBackground.fill(Qt::transparent);

    QPainter bgPainter(&m_cachedBackground);
    bgPainter.setRenderHint(QPainter::Antialiasing, true);

    // Background fill
    bgPainter.fillRect(0, 0, fullW, fullH, QColor(15, 15, 15));

    // Draw border
    bgPainter.setPen(QPen(QColor(60, 60, 60), 1));
    bgPainter.drawRect(marginLeft, marginTop, w, h);

    // Grid
    QPen gridPen(QColor(40, 40, 40));
    gridPen.setWidth(1);
    bgPainter.setPen(gridPen);

    // Vertical grid lines and time labels
    bgPainter.setFont(QFont("Arial", 8));
    for (int i = 0; i <= m_numGridLinesX; ++i) {
      int x = marginLeft + i * w / m_numGridLinesX;
      if (i > 0 && i < m_numGridLinesX) {
        bgPainter.drawLine(x, marginTop, x, marginTop + h);
      }

      double secondsAgo =
          m_timeWindowSec * (1.0 - static_cast<double>(i) / m_numGridLinesX);
      QString label;
      if (secondsAgo < 0.1) {
        label = "now";
      } else {
        label = QString::number(secondsAgo, 'f', 0) +
                "s"; // Remove decimals for cleaner look
      }

      bgPainter.setPen(Qt::lightGray);
      QFontMetrics fm = bgPainter.fontMetrics();
      int labelWidth = fm.horizontalAdvance(label);
      bgPainter.drawText(x - labelWidth / 2, fullH - 8, label);
      bgPainter.setPen(gridPen);
    }

    // Horizontal grid lines and value labels
    for (int i = 0; i <= m_numGridLinesY; ++i) {
      int y = marginTop + i * h / m_numGridLinesY;
      if (i > 0 && i < m_numGridLinesY) {
        bgPainter.drawLine(marginLeft, y, marginLeft + w, y);
      }

      double val =
          m_maxValue - ((m_maxValue - m_minValue) / m_numGridLinesY) * i;
      QString label = QString::number(val, 'f', 2);

      bgPainter.setPen(Qt::lightGray);
      QFontMetrics fm = bgPainter.fontMetrics();
      bgPainter.drawText(8, y + fm.height() / 4, label);
      bgPainter.setPen(gridPen);
    }

    // Title
    bgPainter.setPen(Qt::white);
    bgPainter.setFont(QFont("Arial", 10, QFont::Bold));
    QString title = m_paramName;
    if (!m_units.isEmpty()) {
      title += " (" + m_units + ")";
    }
    bgPainter.drawText(marginLeft, 20, title);

    m_backgroundDirty = false;
  }

  // Render waveform - only when data changes
  if (m_waveformDirty || m_cachedWaveform.size() != widgetSize) {
    m_cachedWaveform = QPixmap(widgetSize);
    m_cachedWaveform.fill(Qt::transparent);

    if (!m_data.empty()) {
      QPainter wfPainter(&m_cachedWaveform);
      wfPainter.setRenderHint(QPainter::Antialiasing, true);

      auto now = std::chrono::steady_clock::now();
      double range = m_maxValue - m_minValue;

      if (!qFuzzyIsNull(range)) {
        // Optimized coordinate conversion functions
        auto timeToX =
            [&](const std::chrono::steady_clock::time_point &timestamp)
            -> double {
          auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
              now - timestamp);
          double secondsAgo =
              std::min(elapsed.count() / 1000.0, m_timeWindowSec);
          double ratio = 1.0 - (secondsAgo / m_timeWindowSec);
          return marginLeft + ratio * w;
        };

        auto valueToY = [&](double val) -> double {
          return marginTop + h - ((val - m_minValue) / range) * h;
        };

        // FIXED: Optimize rendering for large datasets with proper type casting
        size_t dataSize = m_data.size();
        size_t step = std::max(
            static_cast<size_t>(1),
            dataSize / static_cast<size_t>(
                           MAX_RENDERED_POINTS)); // Skip points if too many

        wfPainter.setPen(
            QPen(m_lineColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

        if (dataSize > 1) {
          // Use QPolygonF for better performance with many points
          QPolygonF polygon;
          polygon.reserve(static_cast<int>(dataSize / step + 1));

          for (size_t i = 0; i < dataSize; i += step) {
            const auto &point = m_data[i];
            double x = timeToX(point.timestamp);
            double y = valueToY(point.value);

            // Only add points within visible area (with margin)
            if (x >= marginLeft - 20 && x <= marginLeft + w + 20) {
              polygon << QPointF(x, y);
            }
          }

          // Add the last point if we skipped it
          if (step > 1 && dataSize > 0) {
            const auto &lastPoint = m_data.back();
            double x = timeToX(lastPoint.timestamp);
            double y = valueToY(lastPoint.value);
            if (x >= marginLeft - 20 && x <= marginLeft + w + 20) {
              polygon << QPointF(x, y);
            }
          }

          if (polygon.size() > 1) {
            wfPainter.drawPolyline(polygon);
          }
        } else if (dataSize == 1) {
          // Single point
          double x = timeToX(m_data[0].timestamp);
          double y = valueToY(m_data[0].value);
          wfPainter.drawEllipse(QPointF(x, y), 3, 3);
        }
      }
    }

    m_waveformDirty = false;
  }
}

void WaveformGraph::paint(QPainter *painter) {
  if (width() <= 0 || height() <= 0)
    return;

  // Update cache if needed
  if (shouldUpdateCache()) {
    renderToCache();
  }

  // Simply blit the cached pixmaps - very fast!
  painter->drawPixmap(0, 0, m_cachedBackground);
  painter->drawPixmap(0, 0, m_cachedWaveform);
}
