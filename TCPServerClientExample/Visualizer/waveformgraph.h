#ifndef WAVEFORMGRAPH_H
#define WAVEFORMGRAPH_H

#include <QColor>
#include <QPixmap>
#include <QQuickPaintedItem>
#include <QTimer>
#include <chrono>
#include <deque>

struct DataPoint {
  double value;
  std::chrono::steady_clock::time_point timestamp;

  DataPoint(double v) : value(v), timestamp(std::chrono::steady_clock::now()) {}
};

class WaveformGraph : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(QString paramName READ paramName WRITE setParamName NOTIFY
                 paramNameChanged)
  Q_PROPERTY(QString units READ units WRITE setUnits NOTIFY unitsChanged)
  Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY
                 lineColorChanged)
  Q_PROPERTY(double timeWindowSec READ timeWindowSec WRITE setTimeWindowSec
                 NOTIFY timeWindowSecChanged)
  Q_PROPERTY(double minValue READ minValue NOTIFY minValueChanged)
  Q_PROPERTY(double maxValue READ maxValue NOTIFY maxValueChanged)

public:
  explicit WaveformGraph(QQuickItem *parent = nullptr);

  QString paramName() const { return m_paramName; }
  QString units() const { return m_units; }
  QColor lineColor() const { return m_lineColor; }
  double timeWindowSec() const { return m_timeWindowSec; }
  double minValue() const { return m_minValue; }
  double maxValue() const { return m_maxValue; }

  void setParamName(const QString &name);
  void setUnits(const QString &units);
  void setLineColor(const QColor &color);
  void setTimeWindowSec(double seconds);

  Q_INVOKABLE void appendValue(double val);
  Q_INVOKABLE void clear();

protected:
  void paint(QPainter *painter) override;
  void geometryChanged(const QRectF &newGeometry,
                       const QRectF &oldGeometry) override;

signals:
  void paramNameChanged();
  void unitsChanged();
  void lineColorChanged();
  void timeWindowSecChanged();
  void minValueChanged();
  void maxValueChanged();

private slots:
  void onUpdateTimer();
  void onDataCleanupTimer();

private:
  void updateMinMax();
  void cleanOldData();
  void scheduleUpdate();
  void invalidateCache();
  void renderToCache();
  bool shouldUpdateCache() const;

  QString m_paramName;
  QString m_units;
  QColor m_lineColor;
  double m_timeWindowSec;
  double m_minValue;
  double m_maxValue;

  std::deque<DataPoint> m_data;
  QTimer *m_updateTimer;
  QTimer *m_cleanupTimer;
  bool m_updatePending;

  // Performance optimization - caching
  QPixmap m_cachedBackground;
  QPixmap m_cachedWaveform;
  bool m_backgroundDirty;
  bool m_waveformDirty;
  QSize m_lastSize;

  // Rendering optimization
  mutable bool m_minMaxDirty;
  std::chrono::steady_clock::time_point m_lastDataTime;
  int m_frameSkipCounter;

  // Grid settings
  int m_numGridLinesX = 10;
  int m_numGridLinesY = 8;

  // Performance thresholds
  static constexpr int MAX_RENDERED_POINTS = 1000;
  static constexpr int UPDATE_INTERVAL_MS = 33;    // ~30 FPS
  static constexpr int CLEANUP_INTERVAL_MS = 1000; // 1 second
};

#endif // WAVEFORMGRAPH_H
