#ifndef DIMENVUEDB_H
#define DIMENVUEDB_H

#include "scanList.hpp"
#include <QObject>

class DimenvueDBPrivate;
class BackendMonitor;

class DimenvueDB : public QObject
{
    Q_OBJECT

    // Status
    Q_PROPERTY(float usageTB READ usageTB NOTIFY usageTBChanged)
    Q_PROPERTY(float totalTB READ totalTB NOTIFY totalTBChanged)
    Q_PROPERTY(int batteryCharge READ batteryCharge NOTIFY batteryChargeChanged)
    Q_PROPERTY(bool wifiConnected READ wifiConnected NOTIFY wifiConnectedChanged)
    Q_PROPERTY(int sensorStatus READ sensorStatus NOTIFY sensorStatusChanged)
    Q_PROPERTY(QString time READ time NOTIFY timeChanged)
    // Wifi
    Q_PROPERTY(QStringList ssidList READ ssidList NOTIFY ssidListChanged)
    // Setting
    Q_PROPERTY(int language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString userName READ userName)
    Q_PROPERTY(QString userEmail READ userEmail)
    Q_PROPERTY(QString modelName READ modelName)
    Q_PROPERTY(QString serialNumber READ serialNumber)
    Q_PROPERTY(QString firmwareVersion READ firmwareVersion)
    Q_PROPERTY(QString currentWifiSSID READ currentWifiSSID)
    // Sensors
    Q_PROPERTY(bool sensorInitialized READ sensorInitialized NOTIFY sensorInitializeChanged)
    // ScanView
    Q_PROPERTY(QString scanName READ scanName)
    Q_PROPERTY(QString scanTime READ scanTime)

  public:
    DimenvueDB(QObject *parent = nullptr);
    virtual ~DimenvueDB();

    Q_INVOKABLE void updateTime();
    Q_INVOKABLE void updateWifi();
    Q_INVOKABLE void updateModelData(QObject *model);
    Q_INVOKABLE bool wifiConnect(const QString &ssid, const QString &password);
    Q_INVOKABLE bool login(const QString &id, const QString &password);
    Q_INVOKABLE bool createNewScan(const QString &name, QObject *model);
    Q_INVOKABLE bool initializeSensor();

    Q_INVOKABLE void updateScanNameList();
    Q_INVOKABLE bool isValidScanName(const QString &name) const;

    Q_INVOKABLE void zoomIn();
    Q_INVOKABLE void zoomOut();
    Q_INVOKABLE void setProjectionMode(int mode);
    Q_INVOKABLE bool isLowDensity() const;

    Q_INVOKABLE void setMeasurementMode(bool enable);
    Q_INVOKABLE void resetView();
    Q_INVOKABLE void saveView();
    Q_INVOKABLE void uploadCurrentView();
    Q_INVOKABLE void uploadCheckedView(const std::list<dimenvue::backend::ScanViewPtr> &);
    Q_INVOKABLE void synchronize();

    float usageTB() const;
    float totalTB() const;
    int batteryCharge() const;
    bool wifiConnected() const;
    int sensorStatus() const; // 0: sleep
                              // 1: initialiing
                              // 2: running
    QStringList ssidList() const;

    QString time() const;

    void setLanguage(int language);
    int language() const;
    QString userName() const;
    QString userEmail() const;
    QString modelName() const;
    QString serialNumber() const;
    QString firmwareVersion() const;
    QString currentWifiSSID() const;
    bool sensorInitialized() const;
    QString scanName() const;
    QString scanTime() const;

    void remove(const std::list<dimenvue::backend::ScanViewPtr> &scanNames);
    void setCurrentView(dimenvue::backend::ScanViewPtr &scanView);

    void emitLanguageChange();

    BackendMonitor *monitorObject() const;

  Q_SIGNALS:
    void usageTBChanged();
    void totalTBChanged();
    void batteryChargeChanged();
    void wifiConnectedChanged();
    void sensorStatusChanged();
    void timeChanged();
    void ssidListChanged();
    void languageChanged(int);
    void sensorInitializeChanged();

  private:
    QScopedPointer<DimenvueDBPrivate> d;
};

#endif // DIMENVUEDB_H
