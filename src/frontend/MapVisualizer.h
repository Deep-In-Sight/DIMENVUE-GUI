#pragma once
#include <memory>
#include <OgreEngine.h>
#include <Ogre.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/octree/octree.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloudXYZ;
typedef pcl::octree::OctreePointCloud<pcl::PointXYZ> OctreeXYZ;
typedef OctreeXYZ::DepthFirstIterator DFSIterator;

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

    Ogre::SceneNode *addRandomCloud(int numPoints, float scale = 1.0f);

private:
    MapVisualizer();
    Ogre::ManualObject *createPointCloudObject(PointCloudXYZ::Ptr cloud);

    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
