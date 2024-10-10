#include "plc_siemens.h"

PLC_Siemens::PLC_Siemens(QString ipAddress)
{
    MyS7Client = new TS7Client();
    this->ipAddress = ipAddress;
    connect();
}

bool PLC_Siemens::connect()
{
    if ( !MyS7Client->Connected() )
    {
        return MyS7Client->ConnectTo(ipAddress.toStdString().c_str() ,0,2);
    }
    else {
        return MyS7Client->Connected();
    }
}

void PLC_Siemens::ReadCycle()
{
    int res;
    res = MyS7Client->DBRead(202, 0, 127, &DB_Buffer);
    if (res!=0)
    {
        qDebug()<< "Error read from DB:" << "1 "<<QString::number(res);
    }
    //qDebug()<< "Read from DB:" << "1 "<<QString::number(res);
    else{
        qDebug()<<"Value 0 ="<<DB_Buffer[0];
        qDebug()<<"Value 1 ="<<DB_Buffer[1];
    }
}

uint PLC_Siemens::getUInt16(int Pos)
{
    return getUInt16(DB_Buffer,Pos);
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

uint PLC_Siemens::getUInt32(byte* Buffer, int Pos)
{
    uint Result;
    Result = Buffer[Pos]; Result <<= 8;
    Result |= Buffer[Pos + 1]; Result <<= 8;
    Result |= Buffer[Pos + 2]; Result <<= 8;
    Result |= Buffer[Pos + 3];
    return Result;
}

int PLC_Siemens::getInt32(byte *Buffer, int Pos)
{
    int Result;
    Result = Buffer[Pos]; Result <<= 8;
    Result += Buffer[Pos + 1]; Result <<= 8;
    Result += Buffer[Pos + 2]; Result <<= 8;
    Result += Buffer[Pos + 3];
    return Result;
}

double PLC_Siemens::getReal(byte *Buffer, int Pos)
{
    uint dw = getUInt32(Buffer,Pos);
    return *(pfloat(&dw));
}

void PLC_Siemens::run()
{
    while(true)
    {

        if (MyS7Client->Connected())
        {
            QMutexLocker locker(&mutex);
            ReadCycle();
        }
        else {
            connect();
        }
        // this->sleep(ulong(0.1*10e-6));// 100000us=100ms
        this->sleep(1);
    }
}
