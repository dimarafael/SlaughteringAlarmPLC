#ifndef ALARMLISTMODEL_H
#define ALARMLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include "alarmconfigitem.h"
#include "alarmsconfig.h"

class AlarmListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role {
        AlarmMessageDE = Qt::UserRole + 1,
        AlarmMessageHU = Qt::UserRole + 2,
        AlarmTypeError = Qt::UserRole + 3
    };
    explicit AlarmListModel(QObject *parent = nullptr, AlarmsConfig *almCfg = nullptr);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void processAlarms(QVector<quint8> data);

private:
    AlarmsConfig *alarmsConfig;
    QList<AlarmConfigItem*> m_alarmList;
    QVector<quint8> oldData;
};

#endif // ALARMLISTMODEL_H
