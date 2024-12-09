#include <MapVisualizer.h>
#include <pcl/io/pcd_io.h>
#include <pcl/octree/octree.h>
#include <stack>

#define DEBUG

MapVisualizer::MapVisualizer()
{
}

MapVisualizer::~MapVisualizer() = default;

template <typename PointCloudT>
Ogre::SceneNode *addPointCloud(typename PointCloudT::ConstPtr cloud, const pcl::Indices &indices = pcl::Indices(),
                               Ogre::SceneNode *node = nullptr)
{
    using PointT = typename PointCloudT::PointType;
    constexpr bool hasColor = pcl::traits::has_color<PointT>();

    auto root = OgreEngine::getInstance()->getRoot();
    auto sm = root->getSceneManager("MySceneManager");
    auto mo = sm->createManualObject();
    std::string sMatName = "PointCloudMaterial";

    Ogre::MaterialManager &matMgr = Ogre::MaterialManager::getSingleton();
    if (!matMgr.resourceExists(sMatName))
    {
        Ogre::MaterialPtr pMaterial = matMgr.create(sMatName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        pMaterial->getTechnique(0)->setLightingEnabled(false);
        pMaterial->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        pMaterial->getTechnique(0)->getPass(0)->setVertexColourTracking(Ogre::TVC_EMISSIVE);
    }

    mo->begin(sMatName, Ogre::RenderOperation::OT_POINT_LIST);
    if (indices.empty())
    {
        for (const auto &point : cloud->points)
        {
            mo->position(point.x, point.y, point.z);
            if constexpr (hasColor)
            {
                mo->colour(point.r / 255.0, point.g / 255.0, point.b / 255.0);
            }
            else
            {
                mo->colour(1, 1, 1);
            }
        }
    }
    else
    {
        for (const auto &i : indices)
        {
            auto &point = cloud->points[i];
            mo->position(point.x, point.y, point.z);
            if constexpr (hasColor)
            {
                mo->colour(point.r / 255.0, point.g / 255.0, point.b / 255.0);
            }
            else
            {
                mo->colour(1, 1, 1);
            }
        }
    }
    mo->end();
    auto n = (node) ? node : sm->getRootSceneNode()->createChildSceneNode();
    n->attachObject(mo);
    return n;
}

template <typename PointCloudT> Ogre::SceneNode *addOctreeCloud(const typename PointCloudT::ConstPtr cloud)
{
    using PointT = typename PointCloudT::PointType;
    using OctreeT = pcl::octree::OctreePointCloud<PointT>;
    OctreeT octree(1.0);
    octree.setInputCloud(cloud);
    octree.addPointsFromInputCloud();

    auto root = OgreEngine::getInstance()->getRoot();
    auto sm = root->getSceneManager("MySceneManager");
    auto n = sm->getRootSceneNode()->createChildSceneNode();
    createSceneNodesFromOctree<OctreeT>(octree, n);
    return n;
}

template <typename OctreeT> void createSceneNodesFromOctree(OctreeT &octree, Ogre::SceneNode *rootSceneNode)
{
    using PointCloudT = typename OctreeT::PointCloud;
    for (auto it = octree.leaf_depth_end(); it != octree.leaf_depth_end(); it++)
    {
        auto node = *it;
        auto pointIndices = it.getLeafContainer().getPointIndicesVector();
        auto n = rootSceneNode->createChildSceneNode();
        addPointCloud<PointCloudT>(octree.getInputCloud(), pointIndices, n);
    }
}

Ogre::SceneNode *MapVisualizer::addRandomCloud(int numPoints, float scale)
{
    using PointCloudT = pcl::PointCloud<pcl::PointXYZ>;
    PointCloudT::Ptr cloud(new PointCloudT);
    cloud->points.resize(numPoints);
    for (auto &point : cloud->points)
    {
        Eigen::Vector3f p;
        p.setRandom();
        point.x = p.x() * scale;
        point.y = p.y() * scale;
        point.z = p.z() * scale;
    }

    return addOctreeCloud<PointCloudT>(cloud);
}

Ogre::SceneNode *MapVisualizer::loadPCDFile(const std::string &path)
{
    using PointCloudT = pcl::PointCloud<pcl::PointXYZRGB>;
    PointCloudT::Ptr cloud(new PointCloudT);
    if (pcl::io::loadPCDFile(path, *cloud) == -1)
    {
        throw std::runtime_error("Failed to load PCD file");
    }

    return addOctreeCloud<PointCloudT>(cloud);
}