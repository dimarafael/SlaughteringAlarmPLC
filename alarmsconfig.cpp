#include "alarmsconfig.h"

AlarmsConfig::AlarmsConfig(QObject *parent)
    : QObject{parent}
{
    QFile file(":/Alarms.csv");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    } else {
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            QList<QByteArray> lineSplitted = line.split(',');
            QString messageDE;
            QString messageHU;
            QString alarmType;
            QList<QByteArray> addressSplited;
            QList<QByteArray> byteSplited;
            int addrByte;
            int addrBit;
            bool isTypeError;

            if (lineSplitted.size() < 4) {
                qDebug() << "Alarms.csv parse error : can not split string: " << line;
            } else {
                messageDE = QString::fromUtf8(lineSplitted[0]);
                messageHU = QString::fromUtf8(lineSplitted[1]);
                alarmType = QString::fromUtf8(lineSplitted[3]);
                isTypeError = alarmType.startsWith("Err");

                addressSplited = lineSplitted[2].split(' ');
                if (addressSplited.size() < 4) {
                    qDebug() << "Alarms.csv parse error : can not split address: "
                             << lineSplitted[2];
                } else {
                    byteSplited = addressSplited[3].split('.');
                    if (byteSplited.size() < 2) {
                        qDebug() << "Alarms.csv parse error : can not split byte: "
                                 << addressSplited[3];
                    } else {
                        addrByte = QString::fromUtf8(byteSplited[0]).toInt();
                        addrBit = QString::fromUtf8(byteSplited[1]).toInt();

                        AlarmConfigItem *alarmConfigItem = new AlarmConfigItem(this);
                        alarmConfigItem->setMessageDE(messageDE);
                        alarmConfigItem->setMessageHU(messageHU);
                        alarmConfigItem->setAddrByte(addrByte);
                        alarmConfigItem->setAddrBit(addrBit);
                        alarmConfigItem->setIsTypeError(isTypeError);

                        alarmConfigList.append(alarmConfigItem);

                        // qDebug() << messageHU << " Byte=" << addrByte << " Bit=" << addrBit << " Error=" << isTypeError;
                    }
                }
            }
        }
    }
}

QList<AlarmConfigItem *> AlarmsConfig::getAlarmConfigList() const
{
    return alarmConfigList;
}

AlarmConfigItem *AlarmsConfig::getAlarmConfigItem(int id)
{
    if (id >= 0 and id < alarmConfigList.size()) {
        return alarmConfigList[id];
    } else
        return nullptr;
}

int AlarmsConfig::findAlarmItemId(int byte, int bit)
{
    int i = -1;
    for (i = 0; i < alarmConfigList.size(); i++) {
        if (alarmConfigList[i]->getAddrByte() == byte and alarmConfigList[i]->getAddrBit() == bit) {
            break;
        }
    }
    return i;
}

AlarmConfigItem *AlarmsConfig::getAlarmConfigItem(int byte, int bit)
{
    AlarmConfigItem *item = nullptr;
    for (int i = 0; i < alarmConfigList.size(); i++) {
        if (alarmConfigList[i]->getAddrByte() == byte and alarmConfigList[i]->getAddrBit() == bit) {
            item = alarmConfigList[i];
            break;
        }
    }
    return item;
}
