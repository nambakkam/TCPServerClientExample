#include "tcpclient.h"
#include "commonMessages.h"
#include "encryption.h"
#include "minimalcipher.h"
#include <QDebug>
#include <QJsonDocument>
TcpClient::TcpClient(QObject *parent) : QObject(parent), socket(nullptr) {}

void TcpClient::onThreadStarted() {
  socket = new QTcpSocket(this);
  connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
  connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
  connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
  connect(socket,
          QOverload<QAbstractSocket::SocketError>::of(
              &QAbstractSocket::errorOccurred),
          this, &TcpClient::onError);
  connect(this, &TcpClient::connectRequested, this, &TcpClient::connectToHost,
          Qt::QueuedConnection);
  connect(this, &TcpClient::disconnectRequested, this,
          &TcpClient::disconnectFromHost, Qt::QueuedConnection);

  //  connectToHost(QHostAddress::LocalHost, 12345);
}

void TcpClient::connectToHost(const QString &host, quint16 port) {
  qDebug() << "Connecting to" << host << port;
  socket->connectToHost(host, port);
}

void TcpClient::requestConnect(const QString &host, quint16 port) {
  emit connectRequested(host, port);
}

void TcpClient::requestDisconnect() { emit disconnectRequested(); }

void TcpClient::onConnected() { qDebug() << "Connected to server"; }

void TcpClient::onDisconnected() { qDebug() << "Disconnected from server"; }

void TcpClient::onError(QAbstractSocket::SocketError socketError) {
  Q_UNUSED(socketError);
  qWarning() << "Socket error:" << socket->errorString();
}

void TcpClient::onReadyRead() {
  buffer.append(socket->readAll());
  //  if (!MinimalCipher::initialize(CommonMessages::SECRET_KEY)) {
  //    qDebug() << "Failed to initialize encryption!";
  //    return;
  //  }
  //  buffer = MinimalCipher::decrypt(buffer);
  QJsonObject jsonObj;
  while (CommonMessages::deframeMessage(buffer, jsonObj)) {
    if (!CommonMessages::validateMessage(jsonObj)) {
      qWarning() << "Invalid or unsupported message received:" << jsonObj;
      continue;
    }

    QString paramTypeStr =
        jsonObj[CommonMessages::CommonKeys::PARAMETER_TYPE].toString();
    CommonMessages::MessageType paramType;
    if (!CommonMessages::stringToParameterType(paramTypeStr, paramType)) {
      qWarning() << "Unknown parameterType string:" << paramTypeStr;
      continue;
    }

    QString paramName =
        jsonObj[CommonMessages::CommonKeys::PARAM_NAME].toString();
    QJsonValue val = jsonObj[CommonMessages::CommonKeys::VALUE];
    QString units = jsonObj[CommonMessages::CommonKeys::UNITS].toString();

    emit dataReceived(jsonObj);
    //    MinimalCipher::cleanup();
  }
}

void TcpClient::disconnectFromHost() { socket->disconnectFromHost(); }
