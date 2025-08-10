#include "commonMessages.h"
#include "datahandler.h"
#include "dialindicator.h"
#include "tcpclient.h"
#include "waveformgraph.h"
#include <QGuiApplication>
#include <QHostAddress>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QGuiApplication app(argc, argv);
  QThread tcpThread;
  TcpClient client;
  client.moveToThread(&tcpThread);
  tcpThread.start();
  QObject::connect(&tcpThread, &QThread::started, &client,
                   &TcpClient::onThreadStarted);
  qmlRegisterType<DialIndicator>("CustomControls", 1, 0, "DialIndicator");
  qmlRegisterType<WaveformGraph>("CustomGraphs", 1, 0, "WaveformGraph");

  qmlRegisterUncreatableMetaObject(CommonMessages::staticMetaObject,
                                   "CommonMessages", 1, 0, "CommonMessages",
                                   "Access enums only");
  DataHandler dataHandler;
  QObject::connect(&client, &TcpClient::dataReceived, &dataHandler,
                   &DataHandler::onJsonDataReceived, Qt::AutoConnection);
  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("dataHandler", &dataHandler);
  engine.rootContext()->setContextProperty("tcpClient", &client);
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
