#include "alarmhistorylistmodel.h"

AlarmHistoryListModel::AlarmHistoryListModel(QObject *parent, AlarmsConfig *almCfg)
    : QAbstractListModel{parent}
{
    alarmsConfig = almCfg;
}

int AlarmHistoryListModel::rowCount(const QModelIndex &parent) const
{
    return m_alarmList.size();
}

QVariant AlarmHistoryListModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() >= 0 && index.row() < m_alarmList.size()) {
        AlarmHistoryItem *alarmHistoryItem = m_alarmList[index.row()];
        switch ((Role) role) {
        case AlarmMessageDE:
            return alarmHistoryItem->getMessageDE();
        case AlarmMessageHU:
            return alarmHistoryItem->getMessageHU();
        case AlarmTypeError:
            return alarmHistoryItem->getIsTypeError();
        case AlarmTimestamp:
            return alarmHistoryItem->getTimeStamp();
        }
    }
    return {};
}

QHash<int, QByteArray> AlarmHistoryListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[AlarmMessageDE] = "alarmMessageDE";
    names[AlarmMessageHU] = "alarmMessageHU";
    names[AlarmTypeError] = "alarmTypeError";
    names[AlarmTimestamp] = "alarmTimestamp";
    return names;
}

void AlarmHistoryListModel::processAlarms(QVector<quint8> data)
{
    // qDebug() << "processHistoryAlarms";

    // First initialisation of oldData
    if (oldData.size() != data.size()) {
        for (int i = 0; i < data.size(); i++) {
            oldData.append(0);
        }
    }

    for (int i = 0; i < data.size(); i++) {
        if (data[i] != oldData[i]) {
            for (int bitNumber = 0; bitNumber < 8; bitNumber++) {
                bool alarmBit = (data[i] >> bitNumber) & 1;
                bool oldAlarmBit = (oldData[i] >> bitNumber) & 1;

                // add alarm to list
                if (alarmBit and !oldAlarmBit) {
                    AlarmConfigItem *item = alarmsConfig->getAlarmConfigItem(i, bitNumber);
                    if (item != nullptr) {
                        AlarmHistoryItem *historyItem = new AlarmHistoryItem(this);
                        historyItem->setMessageHU(item->getMessageHU());
                        historyItem->setMessageDE(item->getMessageDE());
                        historyItem->setAddrByte(item->getAddrByte());
                        historyItem->setAddrBit(item->getAddrBit());
                        historyItem->setIsTypeError(item->getIsTypeError());
                        historyItem->setTimeStamp(QDateTime::currentDateTime());

                        beginInsertRows(QModelIndex(), 0 ,0);
                        m_alarmList.prepend(historyItem); // add at first position
                        endInsertRows();
                    }
                }
                // delete old records
                while (m_alarmList.size() > 5) {
                    beginRemoveRows(QModelIndex(), m_alarmList.count() -1, m_alarmList.count() -1);
                    m_alarmList.removeLast();
                    m_alarmList.squeeze();
                    endRemoveRows();
                }
            }
        }
    }

    oldData = data;
    // qDebug()<< "HistorySize " << m_alarmList.size();
}
