#include "dialindicator.h"
#include <QGuiApplication>
#include <QHostAddress>
#include <QQmlApplicationEngine>
#include <tcpclient.h>
int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QGuiApplication app(argc, argv);
  TcpClient client;
  client.connectToHost(QHostAddress::LocalHost, 12345);
  qmlRegisterType<DialIndicator>("CustomControls", 1, 0, "DialIndicator");
  QQmlApplicationEngine engine;
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
