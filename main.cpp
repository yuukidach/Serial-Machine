#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "presenter/mainpresenter.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/view/MainView.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    UartSerial uart_serial;

    engine.rootContext()->setContextProperty("MainPresenter", new MainPresenter(uart_serial));
    engine.load(url);

    return app.exec();
}
