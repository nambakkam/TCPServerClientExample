#ifndef UDPSERVERCOMMUNICATOR_H
#define UDPSERVERCOMMUNICATOR_H

#include "icommunicatorserver.h"
#include <QHostAddress>
#include <QObject>
#include <QSet>
#include <QUdpSocket>

class UdpServerCommunicator : public QObject, public ICommunicatorServer {
  Q_OBJECT
public:
  explicit UdpServerCommunicator(QObject *parent = nullptr);
  ~UdpServerCommunicator() override = default;

  bool startServer(quint16 port) override;
  void stopServer() override;
  bool sendData(const QByteArray &data) override;

  // Send data to the last sender of a datagram
  bool sendDataToLastSender(const QByteArray &data);

signals:
  void datagramReceived(const QByteArray &data, const QHostAddress &sender,
                        quint16 senderPort);

private slots:
  void readPendingDatagrams();

private:
  QUdpSocket *m_socket;
  quint16 m_port;

  // Keep track of last sender
  QHostAddress m_lastSenderAddress;
  quint16 m_lastSenderPort = 0;
};

#endif // UDPSERVERCOMMUNICATOR_H
