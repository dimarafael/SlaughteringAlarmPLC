#include "plc_siemens.h"

PLC_Siemens::PLC_Siemens(QString ipAddress)
{
    MyS7Client = new TS7Client();
    this->ipAddress = ipAddress;
    connectToPLC();
}

PLC_Siemens::~PLC_Siemens()
{
    delete MyS7Client;
}

void PLC_Siemens::run()
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &PLC_Siemens::readData);
    m_timer->start();
}

void PLC_Siemens::readData()
{
    if (MyS7Client->Connected()) {
        int res;
        res = MyS7Client->DBRead(202, 0, DATA_LENGTH, &DB_Buffer);
        if (res != 0) {
            emit isPlcOnline(false);
            reConnectToPLC();
            qDebug() << "Error read from DB:" << "1 " << QString::number(res);
        } else {
            dataToSend.clear();
            dataToSend.squeeze();

            for (int i = 0; i < DATA_LENGTH; i++) {
                dataToSend.append(DB_Buffer[i]);
            }
            emit isPlcOnline(true);
            emit dataReady(dataToSend);
        }
    } else {
        emit isPlcOnline(false);
        connectToPLC();
    }
}

bool PLC_Siemens::connectToPLC()
{
    if (!MyS7Client->Connected()) {
        return MyS7Client->ConnectTo(ipAddress.toStdString().c_str(), 0, 2);
    } else {
        return MyS7Client->Connected();
    }
}

bool PLC_Siemens::reConnectToPLC()
{
    MyS7Client->Disconnect();
    return connectToPLC();
}

uint PLC_Siemens::getUInt16(int Pos)
{
    return getUInt16(DB_Buffer, Pos);
}

uint PLC_Siemens::getUInt16(byte *Buffer, int Pos)
{
    return ((Buffer[Pos] << 8) | Buffer[Pos + 1]);
}

int PLC_Siemens::getInt16(byte *Buffer, int Pos)
{
    return ((Buffer[Pos] << 8) | Buffer[Pos + 1]);
}

int PLC_Siemens::getUInt32(int Pos)
{
    return PLC_Siemens::getUInt32(DB_Buffer, Pos);
}

uint PLC_Siemens::getUInt32(byte *Buffer, int Pos)
{
    uint Result;
    Result = Buffer[Pos];
    Result <<= 8;
    Result |= Buffer[Pos + 1];
    Result <<= 8;
    Result |= Buffer[Pos + 2];
    Result <<= 8;
    Result |= Buffer[Pos + 3];
    return Result;
}

int PLC_Siemens::getInt32(byte *Buffer, int Pos)
{
    int Result;
    Result = Buffer[Pos];
    Result <<= 8;
    Result += Buffer[Pos + 1];
    Result <<= 8;
    Result += Buffer[Pos + 2];
    Result <<= 8;
    Result += Buffer[Pos + 3];
    return Result;
}

double PLC_Siemens::getReal(byte *Buffer, int Pos)
{
    uint dw = getUInt32(Buffer, Pos);
    return *(pfloat(&dw));
}
