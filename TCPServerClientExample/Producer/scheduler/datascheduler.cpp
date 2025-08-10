#include "datascheduler.h"
#include <QDebug>

DataScheduler::DataScheduler(QObject *parent) : QObject(parent) {
  connect(&tickTimer, &QTimer::timeout, this, &DataScheduler::onTick);
  tickTimer.start(baseTickMs);
}

void DataScheduler::addGenerator(std::unique_ptr<IDataGenerator> gen,
                                 int intervalMs) {
  tasks.emplace_back(std::move(gen), intervalMs, intervalMs);
}

void DataScheduler::onTick() {
  for (auto &task : tasks) {
    task.counterMs -= baseTickMs;
    if (task.counterMs <= 0) {
      const auto &value = task.generator->generateData();
      //      qDebug() << task.generator->getParameterName() << ":" << value
      //               << task.generator->getParameterUnits();
      QJsonObject message;
      message[CommonKeys::PARAMETER_TYPE] =
          parameterTypeToString(task.generator->getParameterType());
      message[CommonKeys::PARAM_NAME] = task.generator->getParameterName();
      message[CommonKeys::VALUE] = QJsonValue::fromVariant(value);
      message[CommonKeys::UNITS] = task.generator->getParameterUnits();
      message[CommonKeys::MINVAL] = task.generator->getParameterMinValue();
      message[CommonKeys::MAXVAL] = task.generator->getParameterMaxValue();
      message[CommonKeys::VERSION] = CommonMessages::CURRENT_VERSION;
      emit dataGenerated(message);
      task.counterMs = task.intervalMs; // reset
    }
  }
}
