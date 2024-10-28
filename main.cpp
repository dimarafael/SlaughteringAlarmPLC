#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include "alarmhistorylistmodel.h"
#include "alarmlistmodel.h"
#include "alarmsconfig.h"
#include "plc_siemens.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QThread *threadPLC = new QThread();
    PLC_Siemens *plcSiemens = new PLC_Siemens("10.0.5.5");
    QObject::connect(threadPLC, &QThread::started, plcSiemens, &PLC_Siemens::run);
    plcSiemens->moveToThread(threadPLC);
    threadPLC->start();

    AlarmsConfig *alarmsConfig = new AlarmsConfig(&app);

    AlarmListModel *alarmListModel = new AlarmListModel(&app, alarmsConfig);
    qmlRegisterSingletonInstance("com.kometa.AlarmListModel", 1, 0, "AlarmListModel", alarmListModel);
    QObject::connect(plcSiemens,
                     &PLC_Siemens::dataReady,
                     alarmListModel,
                     &AlarmListModel::processAlarms);
    QObject::connect(plcSiemens,
                     &PLC_Siemens::isPlcOnline,
                     alarmListModel,
                     &AlarmListModel::setOnlineStatus);

    AlarmHistoryListModel *alarmHistoryListModel = new AlarmHistoryListModel(&app, alarmsConfig);
    qmlRegisterSingletonInstance("com.kometa.AlarmHistoryListModel",
                                 1,
                                 0,
                                 "AlarmHistoryListModel",
                                 alarmHistoryListModel);
    QObject::connect(plcSiemens,
                     &PLC_Siemens::dataReady,
                     alarmHistoryListModel,
                     &AlarmHistoryListModel::processAlarms);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SlaughteringAlarmPLC", "Main");

    return app.exec();
}
