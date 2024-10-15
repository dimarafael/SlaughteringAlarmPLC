#include "alarmhistoryitem.h"

AlarmHistoryItem::AlarmHistoryItem(QObject *parent)
    : AlarmConfigItem{parent}
{}

QDateTime AlarmHistoryItem::getTimeStamp() const
{
    return timeStamp;
}

void AlarmHistoryItem::setTimeStamp(const QDateTime &newTimeStamp)
{
    timeStamp = newTimeStamp;
}
