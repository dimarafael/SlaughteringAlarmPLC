#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "plc_siemens.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    PLC_Siemens *plcSiemens;
    plcSiemens = new PLC_Siemens("10.0.5.5");
    plcSiemens->start();

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SlaughteringAlarmPLC", "Main");

    return app.exec();
}
