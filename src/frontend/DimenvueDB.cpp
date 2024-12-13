#include "DimenvueDB.h"

#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QUrl>

#include "context.hpp"
#include "mapVisualizer.hpp"
#include "scanList.hpp"
#include "scanView.hpp"
#include "sensors.hpp"
#include "setting.hpp"
#include "systemStatus.hpp"

#include "BackendMonitor.h"
#include "SpaceDataModel.h"

namespace
{ //=================================================================

} // namespace

//=============================================================================
//  P R I V A T E
//=============================================================================
class DimenvueDBPrivate
{
  public:
    DimenvueDBPrivate(DimenvueDB *q)
        : backend(dimenvue::backend::Context::getInstance()), monitor(new BackendMonitor), q(q)
    {
        thisPtr = this;

        updateTime(time);

        QObject::connect(&timer, &QTimer::timeout, [this]() { updateTime(); });
        timer.setInterval(1000);
        timer.setSingleShot(false);
        timer.start();

        backend.getSystemStatus()->addStatusChangedCallback(systemStatusCallback);
    }

    static DimenvueDBPrivate *thisPtr;
    static dimenvue::backend::SystemStatusCallback systemStatusCallback;
    static std::function<void(bool)> scanViewDirtyCallback;

    float usageTB = 0.0;
    float totalTB = 0.0;
    int batteryCharge = 0;
    bool wifiConnected = false;
    int sensorStatus = 0; // 0:
    QTime time;
    QString timeStr = "";
    int language = -1;
    QTimer timer;
    QStringList ssidList;
    bool sensorInitialized = false;
    std::vector<std::string> scanNameList;
    dimenvue::backend::ScanViewPtr currentView;

    void updateStorage(float usage, float total);
    void updateBattery(float value);
    void updateWifiConnect(bool connect);
    void updateSensorStatus(int status);
    void updateTime(QTime time);
    void updateTime()
    {
        updateTime(QTime::currentTime());
    }
    void updateWifi();

    dimenvue::backend::Context &backend;
    DimenvueDB *q = nullptr;
    QScopedPointer<BackendMonitor> monitor;
};

dimenvue::backend::SystemStatusCallback DimenvueDBPrivate::systemStatusCallback =
    [](const dimenvue::backend::SystemStatus &status) {
        if (thisPtr)
        {
            thisPtr->updateStorage(status.storageStatus.usedGB, status.storageStatus.totalGB);
            thisPtr->updateBattery(status.batteryPercentage);
            thisPtr->updateWifiConnect(status.connectivityStatus);
            thisPtr->updateSensorStatus(status.sensorStatus);
        }
    };

std::function<void(bool)> DimenvueDBPrivate::scanViewDirtyCallback = [](bool dirty) {
    if (thisPtr)
    {
        qDebug() << "ScanViewDirtyCallback: " << dirty;
    }
};

DimenvueDBPrivate *DimenvueDBPrivate::thisPtr = nullptr;

void DimenvueDBPrivate::updateStorage(float usage, float total)
{
    if (usageTB != usage)
    {
        usageTB = usage;
        emit q->usageTBChanged();
    }
    if (totalTB != total)
    {
        totalTB = total;
        emit q->totalTBChanged();
    }
}

void DimenvueDBPrivate::updateBattery(float value)
{
    auto percent = int(value * 100.0);

    if (batteryCharge != percent)
    {
        batteryCharge = percent;
        emit q->batteryChargeChanged();
    }
}

void DimenvueDBPrivate::updateWifiConnect(bool connected)
{
    if (wifiConnected != connected)
    {
        wifiConnected = connected;
        emit q->wifiConnectedChanged();
    }
}

void DimenvueDBPrivate::updateTime(QTime value)
{
    if (time != value)
    {
        time = value;
        if (0 == language)
        {
            timeStr = time.toString("AP hh:mm");
        }
        else
        {
            auto hour = time.hour();
            auto minute = time.minute();
            if (12 < hour)
            {
                timeStr = "AM ";
                hour -= 12;
            }
            else
            {
                timeStr = "PM ";
            }
            auto fill = QChar('0');
            timeStr += QString{"%1:%2"}.arg(hour, 2, 10, fill).arg(minute, 2, 10, fill);
        }
        emit q->timeChanged();
    }
}

void DimenvueDBPrivate::updateSensorStatus(int status)
{
    if (sensorStatus != status)
    {
        sensorStatus = status;
        emit q->sensorStatusChanged();
    }
}

void DimenvueDBPrivate::updateWifi()
{
    auto list = dimenvue::backend::SettingInterface().getSSIDList();
    auto qlist = QStringList{};

    for (auto ssid : list)
    {
        qlist.append(QString::fromStdString(ssid));
    }

    if (ssidList != qlist)
    {
        ssidList = qlist;
        emit q->ssidListChanged();
    }
}

//=============================================================================
//  PUBLIC
//=============================================================================
DimenvueDB::DimenvueDB(QObject *parent) : QObject(parent), d(new DimenvueDBPrivate(this))
{
}

DimenvueDB::~DimenvueDB()
{
}

void DimenvueDB::updateTime()
{
    auto time = QTime::currentTime();

    d->updateTime(time);
}

void DimenvueDB::updateWifi()
{
    d->updateWifi();
}

void DimenvueDB::updateModelData(QObject *object)
{
    auto *model = dynamic_cast<SpaceDataModel *>(object);
    if (model)
    {
        model->clear();
        auto scanList = d->backend.getScanList()->getScanList();
        auto index = 0;
        for (auto viewPtr : scanList)
        {
            auto status = viewPtr->getStats();
            auto name = QString::fromStdString(status.name);
            QDateTime scanTime;
            QUrl thumbnailPath(status.thumbnailPath.c_str());
#if (0)
            model->append(index, name, thumbnailPath, status.areaSizeSqM, scanTime);
#else
            model->append(viewPtr, index);
#endif
            index++;
        }
    }
    else
    {
        qDebug() << "[Error] dynamic_cast<SpaceDataModel*>(" << object << ") failed.";
    }
}

bool DimenvueDB::wifiConnect(const QString &ssid, const QString &password)
{
    auto stdSsid = ssid.toStdString();
    auto stdPassword = password.toStdString();

    auto result = d->backend.getSetting()->connectWifiAsync(stdSsid, stdPassword);

#if (0)
    // TODO : move to thread

    return result.get();
#else
    d->monitor->connectWifi(std::move(result));
#endif
    return false;
}

bool DimenvueDB::login(const QString &id, const QString &password)
{
    auto stdId = id.toStdString();
    auto stdPassword = password.toStdString();

    auto result = d->backend.getSetting()->userLoginAsync(stdId, stdPassword);

#if (0)
    // TODO : move to thread

    return result.get();
#else
    d->monitor->userLogin(std::move(result));

    return false;
#endif
}

bool DimenvueDB::createNewScan(const QString &name, QObject *object)
{
    auto stdName = name.toStdString();

    d->currentView = d->backend.getScanList()->createNewScan(stdName);
    d->currentView->setDirtyCallback(d->scanViewDirtyCallback);
    d->backend.getMapVisualizer()->setScanView(d->currentView);

    auto *model = dynamic_cast<SpaceDataModel *>(object);
    if (model)
    {
        model->append(d->currentView);
    }

    return true;
}

bool DimenvueDB::initializeSensor()
{
    auto ret = d->backend.getSensors()->initializeAsync();

#if (0)
    auto initialzed = ret.get();

    qDebug() << "sensor initialized? " << initialzed;

    if (d->sensorInitialized != initialzed)
    {
        d->sensorInitialized = initialzed;
        emit sensorInitializeChanged();
    }

    return initialzed;
#else
    d->monitor->initializeSensor(std::move(ret));

    return false;
#endif
}

void DimenvueDB::updateScanNameList()
{
    d->scanNameList.clear();

    auto list = d->backend.getScanList()->getScanList();
    for (auto view : list)
    {
        auto status = view->getStats();
        d->scanNameList.push_back(status.name);
    }
}

bool DimenvueDB::isValidScanName(const QString &name) const
{
    if (name.isEmpty())
        return false;

    auto stdName = name.toStdString();
#if (0)
    // link error.
    return d->backend.getScanList()->isScanNameExist(stdName);
#else
    for (auto viewName : d->scanNameList)
    {
        if (viewName == stdName)
        {
            return false;
        }
    }
    return true;
#endif
}

void DimenvueDB::zoomIn()
{
    qDebug() << "[C++] zoomIn()";

    d->backend.getMapVisualizer()->zoomIn();
}

void DimenvueDB::zoomOut()
{
    qDebug() << "[C++] zoomOut()";

    d->backend.getMapVisualizer()->zoomOut();
}

void DimenvueDB::setProjectionMode(int mode)
{
    auto projectionMode = dimenvue::backend::ProjectionMode(mode);

    qDebug() << "setProjectionMode(" << mode << ")";

    d->backend.getMapVisualizer()->setProjectionMode(projectionMode);
}

bool DimenvueDB::isLowDensity() const
{
    return d->currentView->isLowDensity();
}

void DimenvueDB::setMeasurementMode(bool enable)
{
    qDebug() << "setMeasurementMode(" << enable << ")";

    d->backend.getMapVisualizer()->setMeasurementMode(enable);
}

void DimenvueDB::resetView()
{
    qDebug() << "resetView()";

    if (d->currentView)
    {
        d->currentView->reset();
    }
}

void DimenvueDB::saveView()
{
    qDebug() << "saveView()";

    if (d->currentView)
    {
        d->currentView->save();
    }
}

void DimenvueDB::uploadCurrentView()
{
    auto list = std::list<dimenvue::backend::ScanViewPtr>{d->currentView};

    auto ret = d->backend.getScanList()->uploadAsync(list);

    d->monitor->uploadScan(std::move(ret));
}

void DimenvueDB::uploadCheckedView(const std::list<dimenvue::backend::ScanViewPtr> &list)
{
    if (list.size())
    {
        auto ret = d->backend.getScanList()->uploadAsync(list);
        d->monitor->uploadScan(std::move(ret));
    }
}

void DimenvueDB::synchronize()
{
    auto ret = d->backend.getScanList()->synchronizeAllScansAsync();

    d->monitor->synchronizeAllScan(std::move(ret));
}

float DimenvueDB::usageTB() const
{
    return d->usageTB;
}

float DimenvueDB::totalTB() const
{
    return d->totalTB;
}

int DimenvueDB::batteryCharge() const
{
    return d->batteryCharge;
}

bool DimenvueDB::wifiConnected() const
{
    return d->wifiConnected;
}

int DimenvueDB::sensorStatus() const
{
    return d->sensorStatus;
}

QStringList DimenvueDB::ssidList() const
{
    return d->ssidList;
}

QString DimenvueDB::time() const
{
    return d->timeStr;
}

void DimenvueDB::setLanguage(int value)
{
    if (d->language != value)
    {
        d->language = value;
        emit languageChanged(value);
    }
}

int DimenvueDB::language() const
{
    return d->language;
}

QString DimenvueDB::userName() const
{
    auto userInfo = d->backend.getSetting()->getUserInfo();
    auto name = userInfo["Name"];

    return QString::fromStdString(name);
}

QString DimenvueDB::userEmail() const
{
    auto userInfo = d->backend.getSetting()->getUserInfo();
    auto email = userInfo["Email"];

    return QString::fromStdString(email);
}

QString DimenvueDB::modelName() const
{
    auto deviceInfo = d->backend.getSetting()->getDeviceInfo();
    auto model = deviceInfo["Model Name"];

    return QString::fromStdString(model);
}

QString DimenvueDB::serialNumber() const
{
    auto deviceInfo = d->backend.getSetting()->getDeviceInfo();
    auto serial = deviceInfo["Serial Number"];

    return QString::fromStdString(serial);
}

QString DimenvueDB::firmwareVersion() const
{
    auto deviceInfo = d->backend.getSetting()->getDeviceInfo();
    auto version = deviceInfo["Firmware Version"];

    return QString::fromStdString(version);
}

QString DimenvueDB::currentWifiSSID() const
{
    auto ssid = d->backend.getSetting()->getCurrentWifiSSID();

    return QString::fromStdString(ssid);
}

bool DimenvueDB::sensorInitialized() const
{
    auto initialized = d->backend.getSensors()->isInitialized();

    return initialized;
}

QString DimenvueDB::scanName() const
{
    if (d->currentView)
    {
        auto stats = d->currentView->getStats();

        return QString::fromStdString(stats.name);
    }
    else
    {
        return "Default";
    }
}

QString DimenvueDB::scanTime() const
{
    if (d->currentView)
    {
        auto stats = d->currentView->getStats();
        auto createdTime = stats.createdTime;

        auto y = createdTime.tm_year;
        auto m = createdTime.tm_mon;
        auto d = createdTime.tm_mday;

        return QString{"%1-%2-%3"}.arg(y, 4, 10, QChar('0')).arg(m, 2, 10, QChar('0')).arg(d, 2, 10, QChar('0'));
    }
    else
    {
        return "YYYY-MM-DD";
    }
}

void DimenvueDB::remove(const std::list<dimenvue::backend::ScanViewPtr> &list)
{
    auto future = d->backend.getScanList()->deleteAsync(list);

#if (0)
    auto result = future.get();
#else
    d->monitor->deleteScan(std::move(future));
#endif
}

void DimenvueDB::setCurrentView(dimenvue::backend::ScanViewPtr &scanView)
{
    auto stat = scanView->getStats();
    qDebug() << "setCurrentView(" << QString::fromStdString(stat.path) << ")";

    d->backend.getMapVisualizer()->setScanView(scanView);
}

void DimenvueDB::emitLanguageChange()
{
    auto lang = (0 == d->language) ? 0 : 1;

    emit languageChanged(lang);
}

BackendMonitor *DimenvueDB::monitorObject() const
{
    return d->monitor.get();
}
