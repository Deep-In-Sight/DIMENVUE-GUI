#include "BackendMonitor.h"
#include <QTimer>
#include <QVariant>
#include <QDebug>
#include <future>
#include <chrono>

//=============================================================================
//  P R I V A T E
//=============================================================================

class Monitor
{
public:
    Monitor(const char* className, std::future<bool>&& f)
        : className(className)
        , ret(std::move(f))
    {}

    virtual QString name() const {
        return className;
    }
    virtual QVariant value() {
        auto status = ret.wait_for(std::chrono::milliseconds(1));
        if (status == std::future_status::ready) {
            auto result = ret.get();

            qDebug() << "userLogin -> " << result;

            return QVariant{result};
        }
        qDebug() << "future_status not ready!!!";

        return QVariant{};
    }
    virtual void call(QObject* monitorObject, QVariant value) {
        auto methodName = className.toStdString() + "Done";

        if (!QMetaObject::invokeMethod(monitorObject, methodName.c_str(), Qt::DirectConnection, Q_ARG(bool, value.toBool()))) {
            qDebug() << "invokeMethod(" << methodName.c_str() << ") failed";
        }
    }

private:
    QString className;
    std::future<bool> ret;
};

#define MONITOR_INTERVAL    100

class BackendMonitorPrivate
{
public:
    BackendMonitorPrivate(BackendMonitor* object)
        : q(object)
    {
        monitorTimer.setInterval(MONITOR_INTERVAL);
        monitorTimer.setSingleShot(false);
        QObject::connect(&monitorTimer, &QTimer::timeout, [this](){
            for (auto* m : monitorItems) {
                auto v = m->value();

                if (v.isValid()) {
                    m->call(q, v);

                    monitorItems.removeOne(m);
                }
            }
            if (0 == monitorItems.count()) {
                monitorTimer.stop();
                qDebug() << "Monitor timer stop !!!";
            }
        });
    }

    bool add(Monitor* monitor) {
        for (auto* m : monitorItems) {
            if (m->name() == monitor->name()) {
                return false;
            }
        }
        monitorItems.append(monitor);
        if (false == monitorTimer.isActive()) {
            monitorTimer.start();
            qDebug() << "Monitor timer start !!!";
        }

        return true;
    }

    QTimer monitorTimer;
    BackendMonitor* q = nullptr;
    QList<Monitor*> monitorItems;
};

//=============================================================================
//  PUBLIC
//=============================================================================
BackendMonitor::BackendMonitor(QObject* parent)
    : QObject(parent)
    , d(new BackendMonitorPrivate(this))
{}

BackendMonitor::~BackendMonitor()
{}

void BackendMonitor::connectWifi(std::future<bool>&& f)
{
    d->add(new Monitor("connectWifi", std::move(f)));
}

void BackendMonitor::userLogin(std::future<bool>&& f)
{
    d->add(new Monitor("userLogin", std::move(f)));
}

void BackendMonitor::initializeSensor(std::future<bool> &&f)
{
    d->add(new Monitor("initializeSensor", std::move(f)));
}

void BackendMonitor::uploadScan(std::future<bool> &&f)
{
    d->add(new Monitor("uploadScan", std::move(f)));
}

void BackendMonitor::synchronizeAllScan(std::future<bool> &&f)
{
    d->add(new Monitor("synchronizeAllScan", std::move(f)));
}

void BackendMonitor::deleteScan(std::future<bool> &&f)
{
    d->add(new Monitor("deleteScan", std::move(f)));
}
