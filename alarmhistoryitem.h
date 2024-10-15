#ifndef ALARMHISTORYITEM_H
#define ALARMHISTORYITEM_H

#include <QDateTime>
#include "alarmconfigitem.h"

class AlarmHistoryItem : public AlarmConfigItem
{
    Q_OBJECT
public:
    explicit AlarmHistoryItem(QObject *parent = nullptr);

    QDateTime getTimeStamp() const;
    void setTimeStamp(const QDateTime &newTimeStamp);

private:
    QDateTime timeStamp;
};

#endif // ALARMHISTORYITEM_H
