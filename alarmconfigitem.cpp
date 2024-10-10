#include "alarmconfigitem.h"

AlarmConfigItem::AlarmConfigItem(QObject *parent)
    : QObject{parent}
{}

QString AlarmConfigItem::getMessageDE() const
{
    return messageDE;
}

void AlarmConfigItem::setMessageDE(const QString &newMessageDE)
{
    messageDE = newMessageDE;
}

QString AlarmConfigItem::getMessageHU() const
{
    return messageHU;
}

void AlarmConfigItem::setMessageHU(const QString &newMessageHU)
{
    messageHU = newMessageHU;
}

int AlarmConfigItem::getAddrByte() const
{
    return addrByte;
}

void AlarmConfigItem::setAddrByte(int newAddrByte)
{
    addrByte = newAddrByte;
}

int AlarmConfigItem::getAddrBit() const
{
    return addrBit;
}

void AlarmConfigItem::setAddrBit(int newAddrBit)
{
    addrBit = newAddrBit;
}

bool AlarmConfigItem::getIsTypeError() const
{
    return isTypeError;
}

void AlarmConfigItem::setIsTypeError(bool newIsTypeError)
{
    isTypeError = newIsTypeError;
}
