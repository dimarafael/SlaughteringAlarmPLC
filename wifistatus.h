#ifndef WIFISTATUS_H
#define WIFISTATUS_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QTimer>

class WiFiStatus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int wifiState READ wifiState WRITE setWifiState NOTIFY wifiStateChanged FINAL)
public:
    explicit WiFiStatus(QObject *parent = nullptr);

    int wifiState() const;
    void setWifiState(int newWifiState);

signals:
    void wifiStateChanged();
private:
    int m_wifiState;
    QTimer *timer;

private slots:
    void readWiFiState();
};

#endif // WIFISTATUS_H
