#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QByteArray>
#include <QHostAddress>
#include <QJsonObject>
#include <QObject>
#include <QTcpSocket>
class TcpClient : public QObject {
  Q_OBJECT
public:
  explicit TcpClient(QObject *parent = nullptr);
  void connectToHost(const QHostAddress &host, quint16 port);

private slots:
  void onConnected();
  void onDisconnected();
  void onError(QAbstractSocket::SocketError socketError);
  void onReadyRead();

private:
  QTcpSocket *socket;
  QByteArray buffer;
};

#endif // TCPCLIENT_H
