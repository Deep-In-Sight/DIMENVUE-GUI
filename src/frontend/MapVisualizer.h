#pragma once
#include <memory>
#include <OgreEngine.h>
#include <Ogre.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloudXYZ;

class MapVisualizer
{
public:
    static MapVisualizer *getInstance()
    {
        static MapVisualizer instance;
        return &instance;
    }

    MapVisualizer(const MapVisualizer &) = delete;
    MapVisualizer &operator=(const MapVisualizer &) = delete;

    ~MapVisualizer();
    void addPointCloud(PointCloudXYZ::Ptr cloud);
    void addRandomCloud(int numPoints);

private:
    MapVisualizer();
    Ogre::ManualObject *createPointCloudObject(PointCloudXYZ::Ptr cloud);

    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
