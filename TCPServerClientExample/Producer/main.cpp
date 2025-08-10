#include "commonMessages.h"
#include "communication/tcpservercommunicator.h"
#include "encryption.h"
#include "generators/datageneratorfactory.h"
#include "scheduler/datascheduler.h"
#include <QCoreApplication>
int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  DataScheduler scheduler;
  DataGeneratorFactory dataFactory;
  scheduler.addGenerator(dataFactory.create(MessageType::ECG),
                         ScheduledIntervals::ecgTime); // ECG waveform
  scheduler.addGenerator(dataFactory.create(MessageType::PPG),
                         ScheduledIntervals::ppgTime); // PPG waveform
  scheduler.addGenerator(dataFactory.create(MessageType::RespiratoryWaveForm),
                         ScheduledIntervals::respWaveFormTime); // Resp waveform
  scheduler.addGenerator(dataFactory.create(MessageType::HeartRate),
                         ScheduledIntervals::hrTime);
  scheduler.addGenerator(dataFactory.create(MessageType::RespiratoryRate),
                         ScheduledIntervals::rrTime);
  scheduler.addGenerator(dataFactory.create(MessageType::Spo2),
                         ScheduledIntervals::spo2Time);
  scheduler.addGenerator(dataFactory.create(MessageType::NIBPSystole),
                         ScheduledIntervals::NIBPTime);
  scheduler.addGenerator(dataFactory.create(MessageType::NIBPDiastole),
                         ScheduledIntervals::NIBPTime);
  scheduler.addGenerator(dataFactory.create(MessageType::BodyTemp),
                         ScheduledIntervals::tempTime);
  scheduler.addGenerator(dataFactory.create(MessageType::EtCo2),
                         ScheduledIntervals::etco2Time);

  TcpServerCommunicator tcpServer;
  tcpServer.startServer(12345);
  QObject::connect(&scheduler, &DataScheduler::dataGenerated, &tcpServer,
                   [&tcpServer](const QJsonObject &value) {
                     QByteArray message = frameMessage(value);
                     QByteArray encryptedMessage =
                         CommonEncryptor::encryptWithPassword(
                             message, CommonMessages::SECRET_KEY);
                     qDebug() << "Message Published" << message;
                     tcpServer.sendData(encryptedMessage);
                   });

  return a.exec();
}
