#ifndef ALARMCONFIGITEM_H
#define ALARMCONFIGITEM_H

#include <QObject>

class AlarmConfigItem : public QObject
{
    Q_OBJECT
public:
    explicit AlarmConfigItem(QObject *parent = nullptr);

    QString getMessageDE() const;
    void setMessageDE(const QString &newMessageDE);

    QString getMessageHU() const;
    void setMessageHU(const QString &newMessageHU);

    int getAddrByte() const;
    void setAddrByte(int newAddrByte);

    int getAddrBit() const;
    void setAddrBit(int newAddrBit);

    bool getIsTypeError() const;
    void setIsTypeError(bool newIsTypeError);

signals:

private:
    QString messageDE = "";
    QString messageHU = "";
    int addrByte = 0;
    int addrBit = 0;
    bool isTypeError = false;
};

#endif // ALARMCONFIGITEM_H
