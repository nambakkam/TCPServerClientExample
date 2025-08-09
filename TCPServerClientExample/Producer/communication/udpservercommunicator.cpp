#include "udpservercommunicator.h"
#include <QDebug>

UdpServerCommunicator::UdpServerCommunicator(QObject *parent)
    : QObject(parent), m_socket(new QUdpSocket(this)), m_port(0) {
  connect(m_socket, &QUdpSocket::readyRead, this,
          &UdpServerCommunicator::readPendingDatagrams);
}

bool UdpServerCommunicator::startServer(quint16 port) {
  if (m_socket->isOpen())
    m_socket->close();

  if (!m_socket->bind(QHostAddress::LocalHost, port,
                      QUdpSocket::ShareAddress)) {
    qWarning() << "UDP Server failed to bind on port" << port << ":"
               << m_socket->errorString();
    return false;
  }
  m_port = port;
  qDebug() << "UDP Server listening on port" << port;
  return true;
}

void UdpServerCommunicator::stopServer() {
  if (m_socket->isOpen())
    m_socket->close();
}

bool UdpServerCommunicator::sendData(const QByteArray &data) {
  // If you want to keep this generic, sending always to localhost:12346:
  qint64 sent = m_socket->writeDatagram(data, QHostAddress::LocalHost, 12346);
  return (sent == data.size());
}

bool UdpServerCommunicator::sendDataToLastSender(const QByteArray &data) {
  if (m_lastSenderPort == 0) {
    qWarning() << "No known sender to send data back to.";
    return false;
  }
  qint64 sent =
      m_socket->writeDatagram(data, m_lastSenderAddress, m_lastSenderPort);
  if (sent != data.size()) {
    qWarning() << "Failed to send all data to" << m_lastSenderAddress.toString()
               << m_lastSenderPort;
    return false;
  }
  return true;
}

void UdpServerCommunicator::readPendingDatagrams() {
  while (m_socket->hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(int(m_socket->pendingDatagramSize()));
    QHostAddress sender;
    quint16 senderPort;

    m_socket->readDatagram(datagram.data(), datagram.size(), &sender,
                           &senderPort);
    qDebug() << "UDP Server received datagram from" << sender.toString()
             << senderPort << ":" << datagram;

    // Store the sender for replying
    m_lastSenderAddress = sender;
    m_lastSenderPort = senderPort;

    emit datagramReceived(datagram, sender, senderPort);
  }
}
