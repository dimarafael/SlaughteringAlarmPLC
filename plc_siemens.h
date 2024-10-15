#ifndef PLC_SIEMENS_H
#define PLC_SIEMENS_H

#include <QObject>
#include "snap7.h"
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QVector>

#define DATA_LENGTH 127

class PLC_Siemens : public QObject
{

    Q_OBJECT
    typedef float *pfloat;

public:
    enum dataType {eBit, eByte, eInt, eDInt, eWord, eDowrd, eReal};
    PLC_Siemens(QString ipAddress);
    ~PLC_Siemens();

    // Helper functions
    uint getUInt16(int Pos);
    uint getUInt16(byte* Buffer, int Pos);

    int getInt16(int Pos);
    int getInt16(byte* Buffer, int Pos);

    int getUInt32( int Pos);
    uint getUInt32(byte* Buffer, int Pos);

    int getInt32(int Pos);
    int getInt32(byte* Buffer, int Pos);

    double getReal(int Pos);
    double getReal(byte* Buffer, int Pos);

signals:
    void dataReady(QVector<quint8>);

public slots:
    void run();

private slots:
    void readData();

private:
    bool connectToPLC();

    TS7Client *MyS7Client;
    byte DB_Buffer[DATA_LENGTH] = {0};
    QString ipAddress;
    int old_value;
    QTimer *m_timer;
    QVector<quint8> dataToSend;
};

#endif // PLC_SIEMENS_H
