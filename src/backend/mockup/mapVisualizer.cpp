#include <mapVisualizer.hpp>

namespace dimenvue
{
    namespace backend
    {
        struct MapVisualizerInterface::Impl
        {
            void setScanView(const std::shared_ptr<ScanViewInterface> &scanView) { _scanView = scanView; }
            void setMeasurementMode(bool enable) { _measurementMode = enable; }
            bool isMeasurementModeEnabled() { return _measurementMode; }
            void setProjectionMode(ProjectionMode mode) { _projectionMode = mode; }
            ProjectionMode getProjectionMode() { return _projectionMode; }
            void zoomIn() {}
            void zoomOut() {}

            std::shared_ptr<ScanViewInterface> _scanView;
            bool _measurementMode = false;
            ProjectionMode _projectionMode = ProjectionMode::PERSPECTIVE;
        };

        MapVisualizerInterface::MapVisualizerInterface() : _impl(new Impl) {}
        MapVisualizerInterface::~MapVisualizerInterface() = default;

        void MapVisualizerInterface::setScanView(const std::shared_ptr<ScanViewInterface> &scanView)
        {
            _impl->setScanView(scanView);
        }

        void MapVisualizerInterface::setMeasurementMode(bool enable)
        {
            _impl->setMeasurementMode(enable);
        }

        bool MapVisualizerInterface::isMeasurementModeEnabled()
        {
            return _impl->isMeasurementModeEnabled();
        }

        void MapVisualizerInterface::setProjectionMode(ProjectionMode mode)
        {
            _impl->setProjectionMode(mode);
        }

        ProjectionMode MapVisualizerInterface::getProjectionMode()
        {
            return _impl->getProjectionMode();
        }

        void MapVisualizerInterface::zoomIn()
        {
            _impl->zoomIn();
        }

        void MapVisualizerInterface::zoomOut()
        {
            _impl->zoomOut();
        }
    } // namespace backend
} // namespace dimenvue