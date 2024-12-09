#pragma once
#include <Ogre.h>
#include <OgreEngine.h>
#include <memory>
#include <pcl/octree/octree.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

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
    Ogre::SceneNode *loadPCDFile(const std::string &path);

  private:
    MapVisualizer();
    Ogre::ManualObject *createPointCloudObject(PointCloudXYZ::Ptr cloud);
};
