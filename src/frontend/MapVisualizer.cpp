#include <MapVisualizer.h>
#include <pcl/octree/octree.h>
#include <stack>

#define DEBUG

struct MapVisualizer::Impl
{
    int x; // void addPointCloud(PointCloudXYZ::Ptr cloud);
};

MapVisualizer::MapVisualizer()
{
    m_impl = std::make_unique<Impl>();
}

MapVisualizer::~MapVisualizer() = default;

Ogre::SceneNode *addPointCloud(PointCloudXYZ::ConstPtr cloud, const pcl::Indices &indices = pcl::Indices(), Ogre::SceneNode *node = nullptr)
{
    auto root = OgreEngine::getInstance()->getRoot();
    auto sm = root->getSceneManager("MySceneManager");
    auto mo = sm->createManualObject();
    mo->begin("BaseWhite", Ogre::RenderOperation::OT_POINT_LIST);
    if (indices.empty())
    {
        for (const auto &point : cloud->points)
        {
            mo->position(point.x, point.y, point.z);
            mo->colour(1, 1, 1);
        }
    }
    else
    {
        for (const auto &i : indices)
        {
            auto &point = cloud->points[i];
            mo->position(point.x, point.y, point.z);
            mo->colour(1, 1, 1);
        }
    }
    mo->end();
    auto n = (node) ? node : sm->getRootSceneNode()->createChildSceneNode();
    n->attachObject(mo);
    return n;
}

Ogre::SceneNode *createNodeTree(OctreeXYZ &octree);
void createSceneNodesFromOctree(OctreeXYZ &octree, Ogre::SceneNode *rootSceneNode);

Ogre::SceneNode *MapVisualizer::addRandomCloud(int numPoints, float scale)
{
    PointCloudXYZ::Ptr cloud(new PointCloudXYZ);
    cloud->points.resize(numPoints);
    for (auto &point : cloud->points)
    {
        Eigen::Vector3f p;
        p.setRandom();
        point.x = p.x() * scale;
        point.y = p.y() * scale;
        point.z = p.z() * scale;
    }

    return addPointCloud(cloud);

    // put the cloud into an octree
    // OctreeXYZ octree(0.5);
    // octree.setInputCloud(cloud);
    // octree.addPointsFromInputCloud();

    // return createNodeTree(octree);
}

Ogre::SceneNode *createNodeTree(OctreeXYZ &octree)
{
    auto root = OgreEngine::getInstance()->getRoot();
    auto sm = root->getSceneManager("MySceneManager");
    auto treeRoot = sm->getRootSceneNode()
                        ->createChildSceneNode();
    treeRoot->showBoundingBox(true);

    createSceneNodesFromOctree(octree, treeRoot);

    return treeRoot;
}

void createSceneNodesFromOctree(OctreeXYZ &octree, Ogre::SceneNode *rootSceneNode)
{
    DFSIterator it = octree.depth_begin();
    DFSIterator itEnd = octree.depth_end();

    // Stack to keep track of parent SceneNodes at each depth
    std::stack<Ogre::SceneNode *> nodeStack;
    nodeStack.push(rootSceneNode); // Start with the root scene node

    int currentDepth = 0;

    while (it != itEnd)
    {
        auto node = *it;
        auto depth = it.getCurrentOctreeDepth();

        // Pop the stack when moving up in depth
        while (currentDepth > depth)
        {
            nodeStack.pop();
            currentDepth--;
        }

        // Create a new SceneNode for the current octree node
        Ogre::SceneNode *parentSceneNode = nodeStack.top();
        Ogre::SceneNode *currentSceneNode = parentSceneNode->createChildSceneNode();
        // currentSceneNode->showBoundingBox(true);

        if (depth > currentDepth)
        {
            nodeStack.push(currentSceneNode);
            currentDepth = depth;
        }

        if (node->getNodeType() == pcl::octree::LEAF_NODE)
        {
            auto pointIndices = it.getLeafContainer().getPointIndicesVector();
            addPointCloud(octree.getInputCloud(), pointIndices, currentSceneNode);
        }

        ++it; // Move to the next octree node
    }
}