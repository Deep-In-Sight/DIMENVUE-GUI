#pragma once

#include <vector>
#include <future>
#include <functional>
#include <memory>

namespace dimenvue
{
    namespace backend
    {
        enum ConnectivityStatus
        {
            CONNECTED,
            DISCONNECTED
        };

        enum SensorStatus
        {
            SLEEP,
            INITIALIZED,
            RUNNING
        };

        struct StorageStatus
        {
            float usedGB;
            float totalGB;
        };

        struct SystemStatus
        {
            ConnectivityStatus connectivityStatus;
            StorageStatus storageStatus;
            float batteryPercentage;
            SensorStatus sensorStatus;
        };

        using SystemStatusCallback = std::function<void(const SystemStatus &)>;

        /**
         * @brief the interface to provide system status. It is used to periodically update the status of connectivity, storage, battery and sensors.
         *
         */
        class SystemStatusInterface
        {
        public:
            SystemStatusInterface();
            ~SystemStatusInterface();

            /**
             * @brief Set the update frequency of the status.
             *
             * @param hz
             */
            void setUpdateHz(int hz);
            /**
             * @brief Get the Status immediately.
             *
             * @return const SystemStatus&
             */
            const SystemStatus &getStatus();
            /**
             * @brief Add the callback to update the observer of the status.
             *
             * @param cb
             */
            void addStatusChangedCallback(SystemStatusCallback cb);

        private:
            struct Impl;
            std::unique_ptr<Impl> _impl;
        };
    } // namespace backend
} // namespace dimenvue