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

public slots:
  void onThreadStarted();
  void disconnectFromHost();
  void connectToHost(const QString &host, quint16 port);
  Q_INVOKABLE void requestConnect(const QString &host, quint16 port);

  Q_INVOKABLE void requestDisconnect();
private slots:
  void onConnected();
  void onDisconnected();
  void onError(QAbstractSocket::SocketError socketError);
  void onReadyRead();

private:
  QTcpSocket *socket;
  QByteArray buffer;
signals:
  void dataReceived(QJsonObject obj);
  void connectRequested(const QString &host, quint16 port);
  void disconnectRequested();
};

#endif // TCPCLIENT_H
