#include "commonMessages.h"
#include "communication/tcpservercommunicator.h"
#include "communication/udpservercommunicator.h"
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
  scheduler.addGenerator(dataFactory.create(MessageType::HeartRate), 1000);
  scheduler.addGenerator(dataFactory.create(MessageType::RespiratoryRate),
                         5000);
  scheduler.addGenerator(dataFactory.create(MessageType::Spo2), 1000);
  scheduler.addGenerator(dataFactory.create(MessageType::NIBPSystole), 60000);
  scheduler.addGenerator(dataFactory.create(MessageType::NIBPDiastole), 60000);
  scheduler.addGenerator(dataFactory.create(MessageType::BodyTemp), 30000);
  scheduler.addGenerator(dataFactory.create(MessageType::EtCo2), 2000);

  TcpServerCommunicator tcpServer;
  tcpServer.startServer(12345);
  QObject::connect(&scheduler, &DataScheduler::dataGenerated, [&tcpServer]() {
    bool status = tcpServer.sendData("Hello TCP clients!");
    qDebug() << "Sending data over TCP" << status;
  });

  return a.exec();
}
