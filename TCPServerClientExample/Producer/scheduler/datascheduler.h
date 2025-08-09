#ifndef DATASCHEDULER_H
#define DATASCHEDULER_H

#include "../generators/idatagenerator.h"
#include <QObject>
#include <QTimer>
#include <memory>
#include <vector>

class DataScheduler : public QObject {
  Q_OBJECT
public:
  struct Task {
    std::unique_ptr<IDataGenerator> generator;
    int intervalMs; // How often to run
    int counterMs;  // Countdown to next run

    Task(std::unique_ptr<IDataGenerator> gen, int interval, int counter)
        : generator(std::move(gen)), intervalMs(interval), counterMs(counter) {}
  };

  explicit DataScheduler(QObject *parent = nullptr);

  void addGenerator(std::unique_ptr<IDataGenerator> gen, int intervalMs);

private slots:
  void onTick();

private:
  std::vector<Task> tasks; // std::vector instead of QVector
  QTimer tickTimer;
  static constexpr int baseTickMs = 10; // scheduler resolution
};

#endif // DATASCHEDULER_H
