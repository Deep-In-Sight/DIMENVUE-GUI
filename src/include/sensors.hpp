#pragma once

#include <vector>
#include <future>
#include <memory>

namespace dimenvue
{
    namespace backend
    {
        /**
         * @brief the interface to device's sensors. For now just do the initialization.
         * TODO: add more sensor related functions.
         *
         */
        class SensorsInterface
        {
        public:
            /**
             * @brief Construct a new Sensors Interface object. Open the device's sensors.
             *
             */
            SensorsInterface();
            ~SensorsInterface();

            /**
             * @brief check if all sensors are initialized.
             *
             * @return true
             * @return false
             */
            bool isInitialized();
            /**
             * @brief initalize all sensors asynchronously. Return true if all sensors are initialized, false otherwise.
             *
             * @return std::future<bool> caller should check the status of this future, either blocking or non-blocking.
             */
            std::future<bool> initializeAsync();

        private:
            struct Impl;
            std::unique_ptr<Impl> _impl;
        };
    } // namespace backend
} // namespace dimenvue