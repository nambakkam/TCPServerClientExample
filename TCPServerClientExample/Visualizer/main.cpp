#include "commonMessages.h"
#include "dialindicator.h"
#include "parametermodel.h"
#include "tcpclient.h"
#include <QGuiApplication>
#include <QHostAddress>
#include <QQmlApplicationEngine>
#include <QQmlContext>
int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QGuiApplication app(argc, argv);
  TcpClient client;
  client.connectToHost(QHostAddress::LocalHost, 12345);
  qmlRegisterType<DialIndicator>("CustomControls", 1, 0, "DialIndicator");
  qmlRegisterUncreatableMetaObject(CommonMessages::staticMetaObject,
                                   "CommonMessages", 1, 0, "CommonMessages",
                                   "Access enums only");
  ParameterModel model;
  QObject::connect(&client, &TcpClient::dataReceived, &model,
                   &ParameterModel::updateFromJson);
  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("parameterModel", &model);
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
