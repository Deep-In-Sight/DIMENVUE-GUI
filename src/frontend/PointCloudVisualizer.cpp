#include <PointCloudQuickRenderer.h>
#include <PointCloudVisualizer.h>
#include <PointManager.h>
#include <context.hpp>

PointCloudVisualizer::PointCloudVisualizer(QQuickItem *parent) : PointCloudItem(parent), MapVisualizerListener()
{
    auto &backend = dimenvue::backend::Context::getInstance();
    backend.getMapVisualizer()->addListener(this);
    qDebug() << "added listener to map visualizer backend";
}

PointCloudVisualizer::~PointCloudVisualizer()
{
    auto &backend = dimenvue::backend::Context::getInstance();
    backend.getMapVisualizer()->removeListener(this);
    qDebug() << "removed listener to map visualizer backend";
}

void PointCloudVisualizer::onNewPointCloud(const dimenvue::backend::PointCloud::Ptr pcd)
{
    m_renderer->pointLoader->addPoints(pcd);
    // this callback likely called from ros spinning thread so can't call update directly
    QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
}