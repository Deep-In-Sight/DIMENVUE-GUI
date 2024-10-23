#include <systemStatus.hpp>

namespace dimenvue
{
    namespace backend
    {
        struct SystemStatusInterface::Impl
        {
            Impl() : _running(true), _updateHz(1) {}
            ~Impl()
            {
                _running = false;
                if (_thread.joinable())
                {
                    _thread.join();
                }
            }
            void start()
            {
                _thread = std::thread(&Impl::run, this);
            }

            void run()
            {
                while (_running)
                {
                    _status.connectivityStatus = _getConnectStatus();
                    _status.storageStatus = _getStorageStatus();
                    _status.batteryPercentage = _getBatteryPercentage();
                    _status.sensorStatus = _getSensorStatus();
                    for (auto &cb : _callbacks)
                    {
                        cb(_status);
                    }

                    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / _updateHz));
                }
            }

            ConnectivityStatus _getConnectStatus()
            {
                return ConnectivityStatus::CONNECTED;
            }
            StorageStatus _getStorageStatus()
            {
                return StorageStatus{0.5f, 1.0f};
            }
            float _getBatteryPercentage()
            {
                return 0.5f;
            }
            SensorStatus _getSensorStatus()
            {
                return SensorStatus::RUNNING;
            }

            std::thread _thread;
            bool _running;
            int _updateHz;
            SystemStatus _status;
            std::vector<SystemStatusCallback> _callbacks;
        };

        SystemStatusInterface::SystemStatusInterface() : _impl(new Impl)
        {
            setUpdateHz(1);
            _impl->start();
        }

        SystemStatusInterface::~SystemStatusInterface() = default;

        void SystemStatusInterface::setUpdateHz(int hz)
        {
            _impl->_updateHz = hz;
        }

        const SystemStatus &SystemStatusInterface::getStatus()
        {
            return _impl->_status;
        }

        void SystemStatusInterface::addStatusChangedCallback(SystemStatusCallback cb)
        {
            _impl->_callbacks.push_back(cb);
        }

    }
}