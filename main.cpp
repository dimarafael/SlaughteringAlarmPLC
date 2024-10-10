#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "plc_siemens.h"
#include "alarmsconfig.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    PLC_Siemens *plcSiemens = new PLC_Siemens("10.0.5.5");
    // plcSiemens->start();

    AlarmsConfig *alarmsConfig = new AlarmsConfig(&app);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SlaughteringAlarmPLC", "Main");

    return app.exec();
}
