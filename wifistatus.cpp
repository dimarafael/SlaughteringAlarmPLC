#include "wifistatus.h"

WiFiStatus::WiFiStatus(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WiFiStatus::readWiFiState);
    timer->start(1000);
}

int WiFiStatus::wifiState() const
{
    return m_wifiState;
}

void WiFiStatus::setWifiState(int newWifiState)
{
    if (m_wifiState == newWifiState)
        return;
    m_wifiState = newWifiState;
    emit wifiStateChanged();
}

void WiFiStatus::readWiFiState()
{
    QFile file("/proc/net/wireless");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray contents = file.readAll();
        file.close();

        QTextStream in(&contents);
        bool connected = false;
        float signalLevel = 0;

        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.contains("wlan0")) {
                connected = true;
                QStringList fields = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
                if (fields.size() > 3) {
                    signalLevel = 2 * (fields[3].toFloat() + 100);
                    // int signalPercent = 2 * (signalLevel + 100);
                     // setText(QString("Signal Strength: %1%\nStatus: Connected").arg(signalPercent));
                }
                break;
            }
        }

        if (!connected) {
            setWifiState(0);
            // qDebug()<< "WiFi disconnected";
        } else{
            if (signalLevel < 25){
                setWifiState(1);
            } else if(signalLevel  < 50){
                setWifiState(2);
            } else if(signalLevel < 75){
                setWifiState(3);
            } else {
                setWifiState(4);
            };
            // qDebug() << "WiFi : " << signalLevel << "db |" << (2 * (signalLevel + 100)) << "%";
        }
    }
}
