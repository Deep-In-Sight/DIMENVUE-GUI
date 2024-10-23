#pragma once

#include <memory>

namespace dimenvue
{
    namespace backend
    {
        class SensorsInterface;
        class ScanListInterface;
        class SystemStatusInterface;
        class ScanViewInterface;
        class SettingInterface;
        class MapVisualizerInterface;

        /**
         * @brief a global context that hold variables to access from anywhere
         *
         */
        class Context
        {
        public:
            static Context &getInstance();

            std::shared_ptr<SensorsInterface> getSensors() { return _pSensorsInterface; };
            std::shared_ptr<ScanListInterface> getScanList() { return _pScanListInterface; };
            std::shared_ptr<SystemStatusInterface> getSystemStatus() { return _pSystemStatusInterface; };
            std::shared_ptr<MapVisualizerInterface> getMapVisualizer() { return _pMapVisualizerInterface; };
            std::shared_ptr<SettingInterface> getSetting() { return _pSettingInterface; };

        private:
            Context();
            Context(const Context &) = delete;
            Context &operator=(const Context &) = delete;

            std::shared_ptr<SensorsInterface> _pSensorsInterface;
            std::shared_ptr<MapVisualizerInterface> _pMapVisualizerInterface;
            std::shared_ptr<ScanListInterface> _pScanListInterface;
            std::shared_ptr<SystemStatusInterface> _pSystemStatusInterface;
            std::shared_ptr<SettingInterface> _pSettingInterface;
        };
    } // namespace backend
} // namespace dimenvue
