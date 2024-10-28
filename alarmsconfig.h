#ifndef ALARMSCONFIG_H
#define ALARMSCONFIG_H

#include <QDebug>
#include <QFile>
#include <QList>
#include <QObject>
#include "alarmconfigitem.h"

class AlarmsConfig : public QObject
{
    Q_OBJECT
public:
    explicit AlarmsConfig(QObject *parent = nullptr);

    QList<AlarmConfigItem *> getAlarmConfigList() const;
    AlarmConfigItem *getAlarmConfigItem(int id);
    int findAlarmItemId(int byte, int bit);
    AlarmConfigItem *getAlarmConfigItem(int byte, int bit);

private:
    QList<AlarmConfigItem *> alarmConfigList;
};

#endif // ALARMSCONFIG_H
