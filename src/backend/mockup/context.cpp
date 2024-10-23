#include <context.hpp>
#include <scanView.hpp>
#include <scanList.hpp>
#include <systemStatus.hpp>
#include <sensors.hpp>
#include <setting.hpp>
#include <mapVisualizer.hpp>

namespace dimenvue
{
    namespace backend
    {
        Context &Context::getInstance()
        {
            static Context instance;
            return instance;
        }

        Context::Context()
        {
            _pSensorsInterface = std::make_shared<SensorsInterface>();
            _pScanListInterface = std::make_shared<ScanListInterface>();
            _pSystemStatusInterface = std::make_shared<SystemStatusInterface>();
            _pMapVisualizerInterface = std::make_shared<MapVisualizerInterface>();
            _pSettingInterface = std::make_shared<SettingInterface>();
        }
    }
}
