#ifndef BACKENDMONITOR_H
#define BACKENDMONITOR_H

#include <QObject>
#include <future>

class BackendMonitorPrivate;

class BackendMonitor : public QObject
{
    Q_OBJECT

public:
    BackendMonitor(QObject* parent = nullptr);
    virtual ~BackendMonitor();

    //-------------------------------------------------------------------------
    //  Request
    //-------------------------------------------------------------------------
    //  setting
    void connectWifi(std::future<bool>&&);
    void userLogin(std::future<bool>&&);
    //  sensors
    void initializeSensor(std::future<bool>&&);
    //  scanList
    void uploadScan(std::future<bool>&&);
    void synchronizeAllScan(std::future<bool>&&);
    void deleteScan(std::future<bool>&&);

Q_SIGNALS:
    //-------------------------------------------------------------------------
    //  Response
    //-------------------------------------------------------------------------
    void connectWifiDone(bool value);
    void userLoginDone(bool value);
    void initializeSensorDone(bool value);
    void uploadScanDone(bool value);
    void synchronizeAllScanDone(bool value);
    void deleteScanDone(bool value);

private:
    QScopedPointer<BackendMonitorPrivate> d;
};

#endif // BACKENDMONITOR_H
