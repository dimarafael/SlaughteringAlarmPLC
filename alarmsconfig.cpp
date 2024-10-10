#include "alarmsconfig.h"

AlarmsConfig::AlarmsConfig() {
    QFile file (":/Alarms.csv");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    } else {
        qDebug() << "----------------";
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            QList<QByteArray> lineSplitted = line.split(',');
            QByteArray messageDE;
            QByteArray messageHU;
            QByteArray alarmType;
            QList<QByteArray> addressSplited;
            QList<QByteArray> byteSplited;
            int addrByte;
            int addrBit;

            if(lineSplitted.size() < 4){
                qDebug() << "Alarms.csv parse error : can not split string: " << line;
            } else{
                messageDE = lineSplitted[0];
                messageHU = lineSplitted[1];
                alarmType = lineSplitted[3];
                addressSplited = lineSplitted[2].split(' ');
                if(addressSplited.size() < 4){
                    qDebug() << "Alarms.csv parse error : can not split address: " << lineSplitted[2];
                } else {
                    byteSplited = addressSplited[3].split('.');
                    if(byteSplited.size() < 2){
                        qDebug() << "Alarms.csv parse error : can not split byte: " << addressSplited[3];
                    } else {
                        addrByte = QString::fromUtf8(byteSplited[0]).toInt();
                        addrBit = QString::fromUtf8(byteSplited[1]).toInt();

                        // qDebug() << QString::fromUtf8(messageHU) << " Byte=" << addrByte << " Bit=" << addrBit;
                    }
                }
            }
            // wordList.append(line.split(',').first());
            // qDebug() << line.split(',')[1] << " | " << line.split(',')[2] << ": byte=" << line.split(',')[2].split(' ')[3].split('.')[0] << " bit=" << line.split(',')[2].split(' ')[3].split('.')[1];
        }
    }

}
