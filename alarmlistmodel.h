#ifndef ALARMLISTMODEL_H
#define ALARMLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QObject>
#include "alarmactiveitem.h"
#include "alarmsconfig.h"

class AlarmListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool plcOnline READ plcOnline WRITE setPlcOnline NOTIFY plcOnlineChanged FINAL)
public:
    enum Role {
        AlarmMessageDE = Qt::UserRole + 1,
        AlarmMessageHU = Qt::UserRole + 2,
        AlarmTypeError = Qt::UserRole + 3,
        AlarmTimestamp = Qt::UserRole + 4
    };
    explicit AlarmListModel(QObject *parent = nullptr, AlarmsConfig *almCfg = nullptr);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    bool plcOnline() const;
    void setPlcOnline(bool newPlcOnline);

public slots:
    void processAlarms(QVector<quint8> data);
    void setOnlineStatus(bool isOnline);

signals:
    void plcOnlineChanged();

private:
    AlarmsConfig *alarmsConfig;
    QList<AlarmActiveItem *> m_alarmList;
    QVector<quint8> oldData;
    bool m_plcOnline;
};

#endif // ALARMLISTMODEL_H
