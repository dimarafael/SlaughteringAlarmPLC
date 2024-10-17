#ifndef ALARMACTIVEITEM_H
#define ALARMACTIVEITEM_H

#include "alarmhistoryitem.h"

class AlarmActiveItem : public AlarmHistoryItem
{
    Q_OBJECT
public:
    explicit AlarmActiveItem(QObject *parent = nullptr);

private:

};

#endif // ALARMACTIVEITEM_H
