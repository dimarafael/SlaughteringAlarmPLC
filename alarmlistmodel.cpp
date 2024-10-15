#include "alarmlistmodel.h"

AlarmListModel::AlarmListModel(QObject *parent, AlarmsConfig *almCfg)
    : QAbstractListModel{parent}
{
    alarmsConfig = almCfg;
}

int AlarmListModel::rowCount(const QModelIndex &parent) const
{
    return m_alarmList.size();
}

QVariant AlarmListModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.row() >= 0 && index.row() < m_alarmList.size()){
        AlarmConfigItem *alarmConfigItem = m_alarmList[index.row()];
        switch ((Role)role) {
        case AlarmMessageDE:
            return alarmConfigItem->getMessageDE();
        case AlarmMessageHU:
            return alarmConfigItem->getMessageHU();
        case AlarmTypeError:
            return alarmConfigItem->getIsTypeError();
        }
    }
    return {};
}

QHash<int, QByteArray> AlarmListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[AlarmMessageDE] = "alarmMessageDE";
    names[AlarmMessageHU] = "alarmMessageHU";
    names[AlarmTypeError] = "alarmTypeError";
    return names;
}

void AlarmListModel::processAlarms(QVector<quint8> data)
{
    qDebug() << "processAlarms";

    // First initialisation of oldData
    if(oldData.size() != data.size()){
        for (int i = 0; i < data.size() ;i++){
            oldData.append(0);
        }
    }

    beginResetModel();

    for (int i = 0; i < data.size() ;i++){
        if(data[i] != oldData[i]){
            for(int bitNumber = 0; bitNumber < 8; bitNumber++){
                bool alarmBit = (data[i] >> bitNumber) & 1;
                bool oldAlarmBit = (oldData[i] >> bitNumber) & 1;

                // add alarm to list
                if(alarmBit and !oldAlarmBit){
                    AlarmConfigItem *item = alarmsConfig->getAlarmConfigItem(i,bitNumber);
                    if (item != nullptr){
                        m_alarmList.append(item);
                    }
                }

                // remove alarm from list
                if(!alarmBit and oldAlarmBit){
                    for(int j = 0; j < m_alarmList.size(); j++){
                        if(m_alarmList[j]->getAddrByte() == i and m_alarmList[j]->getAddrBit() == bitNumber){
                            m_alarmList.remove(j,1);
                            m_alarmList.squeeze();
                        }
                    }
                }
            }
        }
    }
    oldData = data;
    endResetModel();
    qDebug()<< "Size " << m_alarmList.size();
}

