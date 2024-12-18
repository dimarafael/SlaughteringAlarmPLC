#ifndef ALARMHISTORYLISTMODEL_H
#define ALARMHISTORYLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QObject>
#include "alarmhistoryitem.h"
#include "alarmsconfig.h"

class AlarmHistoryListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role {
        AlarmMessageDE = Qt::UserRole + 1,
        AlarmMessageHU = Qt::UserRole + 2,
        AlarmTypeError = Qt::UserRole + 3,
        AlarmTimestamp = Qt::UserRole + 4
    };
    explicit AlarmHistoryListModel(QObject *parent = nullptr, AlarmsConfig *almCfg = nullptr);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void processAlarms(QVector<quint8> data);

private:
    AlarmsConfig *alarmsConfig;
    QList<AlarmHistoryItem *> m_alarmList;
    QVector<quint8> oldData;
};

#endif // ALARMHISTORYLISTMODEL_H
