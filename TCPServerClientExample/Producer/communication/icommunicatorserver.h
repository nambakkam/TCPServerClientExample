#ifndef ICOMMUNICATORSERVER_H
#define ICOMMUNICATORSERVER_H

#include <QByteArray>
#include <QString>

class ICommunicatorServer {
public:
  virtual ~ICommunicatorServer() = default;

  // Start listening / binding
  virtual bool startServer(quint16 port) = 0;

  // Stop server
  virtual void stopServer() = 0;

  // Send data to clients or broadcast
  virtual bool sendData(const QByteArray &data) = 0;
};

#endif // ICOMMUNICATORSERVER_H
