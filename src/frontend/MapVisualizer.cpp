#include <MapVisualizer.h>

struct MapVisualizer::Impl
{
    int x; // void addPointCloud(PointCloudXYZ::Ptr cloud);
};

MapVisualizer::MapVisualizer()
{
    m_impl = std::make_unique<Impl>();
}

MapVisualizer::~MapVisualizer() = default;

void MapVisualizer::addPointCloud(PointCloudXYZ::Ptr cloud)
{
    auto root = OgreEngine::getInstance()->getRoot();
    auto sm = root->getSceneManager("MySceneManager");
    auto mo = sm->createManualObject();
    mo->begin("BaseWhite", Ogre::RenderOperation::OT_POINT_LIST);
    for (const auto &point : cloud->points)
    {
        mo->position(point.x, point.y, point.z);
        mo->colour(1, 1, 1);
    }
    mo->end();
    sm->getRootSceneNode()
        ->createChildSceneNode()
        ->attachObject(mo);
}

void MapVisualizer::addRandomCloud(int numPoints)
{
    PointCloudXYZ::Ptr cloud(new PointCloudXYZ);
    cloud->points.resize(numPoints);
    for (auto &point : cloud->points)
    {
        point.x = rand() % 100;
        point.y = rand() % 100;
        point.z = rand() % 100;
    }
    addPointCloud(cloud);
}