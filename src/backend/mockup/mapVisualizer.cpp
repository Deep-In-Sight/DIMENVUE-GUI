#include <mapVisualizer.hpp>

namespace dimenvue
{
namespace backend
{
struct MapVisualizerInterface::Impl
{
    Impl()
    {
        auto msgCallback = [this](const PointCloud::Ptr msg) {
            // PointCloudPtr cloud(new PointCloud);
            std::cout << "received pcd with " << msg->points.size() << " points" << std::endl;

            for (auto listener : _listeners)
            {
                listener->onNewPointCloud(msg);
            }
        };
        _rosInterface.setLidarCallback(msgCallback);
    }

    void addListener(MapVisualizerListener *listener)
    {
        _listeners.push_back(listener);
    }

    void removeListener(MapVisualizerListener *listener)
    {
        _listeners.erase(std::remove(_listeners.begin(), _listeners.end(), listener), _listeners.end());
    }

    void setScanView(const std::shared_ptr<ScanViewInterface> &scanView)
    {
        _scanView = scanView;
    }
    void setMeasurementMode(bool enable)
    {
        _measurementMode = enable;
    }
    bool isMeasurementModeEnabled()
    {
        return _measurementMode;
    }
    void setProjectionMode(ProjectionMode mode)
    {
        _projectionMode = mode;
    }
    ProjectionMode getProjectionMode()
    {
        return _projectionMode;
    }
    void zoomIn()
    {
    }
    void zoomOut()
    {
    }

    std::shared_ptr<ScanViewInterface> _scanView;
    bool _measurementMode = false;
    ProjectionMode _projectionMode = ProjectionMode::PERSPECTIVE;
    RosInterface _rosInterface;
    std::vector<MapVisualizerListener *> _listeners;
};

MapVisualizerInterface::MapVisualizerInterface() : _impl(new Impl)
{
}
MapVisualizerInterface::~MapVisualizerInterface() = default;

void MapVisualizerInterface::addListener(MapVisualizerListener *listener)
{
    _impl->addListener(listener);
}

void MapVisualizerInterface::removeListener(MapVisualizerListener *listener)
{
    _impl->removeListener(listener);
}

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

MapVisualizerListener::MapVisualizerListener() = default;
MapVisualizerListener::~MapVisualizerListener() = default;
void MapVisualizerListener::onNewPointCloud(const PointCloud::Ptr pcd)
{
}

} // namespace backend
} // namespace dimenvue