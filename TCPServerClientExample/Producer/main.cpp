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
                         40); // ECG waveform
  scheduler.addGenerator(dataFactory.create(MessageType::PPG),
                         10); // PPG waveform
  scheduler.addGenerator(dataFactory.create(MessageType::RespiratoryWaveForm),
                         40); // Resp waveform
  scheduler.addGenerator(dataFactory.create(MessageType::HeartRate), 500);
  scheduler.addGenerator(dataFactory.create(MessageType::RespiratoryRate), 500);
  scheduler.addGenerator(dataFactory.create(MessageType::Spo2), 500);
  scheduler.addGenerator(dataFactory.create(MessageType::NIBPSystole), 2000);
  scheduler.addGenerator(dataFactory.create(MessageType::NIBPDiastole), 2000);
  scheduler.addGenerator(dataFactory.create(MessageType::BodyTemp), 3000);
  scheduler.addGenerator(dataFactory.create(MessageType::EtCo2), 2000);

  TcpServerCommunicator tcpServer;
  tcpServer.startServer(12345);
  QObject::connect(&scheduler, &DataScheduler::dataGenerated, &tcpServer,
                   [&tcpServer](const QJsonObject &value) {
                     QByteArray message = frameMessage(value);
                     QByteArray encryptedMessage =
                         CommonEncryptor::encryptWithPassword(
                             message, CommonMessages::SECRET_KEY);
                     //                     qDebug() << "Message Published"
                     //                     << message;
                     tcpServer.sendData(encryptedMessage);
                   });

  return a.exec();
}
