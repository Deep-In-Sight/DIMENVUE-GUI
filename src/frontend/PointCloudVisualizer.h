#pragma once

#include <PointCloudItem.h>
#include <mapVisualizer.hpp>

class PointCloudVisualizer : public PointCloudItem, public dimenvue::backend::MapVisualizerListener
{
    Q_OBJECT
  public:
    PointCloudVisualizer(QQuickItem *parent = nullptr);
    ~PointCloudVisualizer();

    void onNewPointCloud(const dimenvue::backend::PointCloud::Ptr pcd) override;
};