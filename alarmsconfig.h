#ifndef ALARMSCONFIG_H
#define ALARMSCONFIG_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QList>
#include "alarmconfigitem.h"

class AlarmsConfig : public QObject
{
    Q_OBJECT
public:
    explicit AlarmsConfig(QObject *parent = nullptr);

    QList<AlarmConfigItem *> getAlarmConfigList() const;

private:
    QList<AlarmConfigItem*> alarmConfigList;
};

#endif // ALARMSCONFIG_H
