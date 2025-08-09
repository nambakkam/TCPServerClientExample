#include "tcpservercommunicator.h"
#include <QDebug>

TcpServerCommunicator::TcpServerCommunicator(QObject *parent)
    : QObject(parent) {
  m_server = new QTcpServer(this);
  connect(m_server, &QTcpServer::newConnection, this,
          &TcpServerCommunicator::onNewConnection);
}

TcpServerCommunicator::~TcpServerCommunicator() { stopServer(); }

bool TcpServerCommunicator::startServer(quint16 port) {
  if (!m_server->listen(QHostAddress::LocalHost, port)) {
    qWarning() << "TCP Server failed to start:" << m_server->errorString();
    return false;
  }
  qDebug() << "TCP Server listening on port" << port;
  return true;
}

void TcpServerCommunicator::stopServer() {
  for (QTcpSocket *client : qAsConst(m_clients)) {
    client->disconnectFromHost();
    client->deleteLater();
  }
  m_clients.clear();

  if (m_server->isListening()) {
    m_server->close();
  }
}

bool TcpServerCommunicator::sendData(const QByteArray &data) {
  bool success = true;
  for (QTcpSocket *client : qAsConst(m_clients)) {
    if (client->state() == QAbstractSocket::ConnectedState) {
      qint64 written = client->write(data);
      if (written != data.size()) {
        qWarning() << "Failed to send full data to a client";
        success = false;
      }
      client->flush();
    }
  }
  return success;
}

void TcpServerCommunicator::onNewConnection() {
  while (m_server->hasPendingConnections()) {
    QTcpSocket *clientSocket = m_server->nextPendingConnection();
    qDebug() << "New TCP client connected from"
             << clientSocket->peerAddress().toString();

    m_clients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::disconnected, this,
            &TcpServerCommunicator::onClientDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this,
            &TcpServerCommunicator::onReadyRead);
  }
}

void TcpServerCommunicator::onClientDisconnected() {
  QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
  if (client) {
    qDebug() << "TCP client disconnected:" << client->peerAddress().toString();
    m_clients.removeAll(client);
    client->deleteLater();
  }
}

void TcpServerCommunicator::onReadyRead() {
  QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
  if (!client)
    return;

  QByteArray data = client->readAll();
  qDebug() << "Received from client" << client->peerAddress().toString() << ":"
           << data;
  // You can handle client data here if needed
}
