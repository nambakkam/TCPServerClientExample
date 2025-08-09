#ifndef TCPSERVERCOMMUNICATOR_H
#define TCPSERVERCOMMUNICATOR_H

#include "icommunicatorserver.h"
#include <QList>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServerCommunicator : public QObject, public ICommunicatorServer {
  Q_OBJECT
public:
  explicit TcpServerCommunicator(QObject *parent = nullptr);
  ~TcpServerCommunicator() override;

  bool startServer(quint16 port) override;
  void stopServer() override;
  bool sendData(const QByteArray &data) override;

private slots:
  void onNewConnection();
  void onClientDisconnected();
  void onReadyRead();

private:
  QTcpServer *m_server;
  QList<QTcpSocket *> m_clients; // Track connected clients
};

#endif // TCPSERVERCOMMUNICATOR_H
