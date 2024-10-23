#include <sensors.hpp>
#include <thread>

namespace dimenvue
{
    namespace backend
    {
        struct SensorsInterface::Impl
        {
            Impl() : isInitialized(false) {}
            bool initialize()
            {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                isInitialized = true;
                return true;
            }
            bool isInitialized;
        };

        SensorsInterface::SensorsInterface() : _impl(new Impl) {}
        SensorsInterface::~SensorsInterface() = default;

        bool SensorsInterface::isInitialized() { return _impl->isInitialized; }
        std::future<bool> SensorsInterface::initializeAsync()
        {
            return std::async(std::launch::async, [this]
                              { return _impl->initialize(); });
        }

    } // namespace backend
} // namespace dimenvue