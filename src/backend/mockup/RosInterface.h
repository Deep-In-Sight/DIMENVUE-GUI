#pragma once

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

namespace dimenvue
{
namespace backend
{
typedef sensor_msgs::msg::PointCloud2 PointCloud2Msg;
typedef pcl::PointXYZRGBNormal PointType;
typedef pcl::PointCloud<PointType> PointCloud;
typedef std::function<void(const PointCloud::Ptr)> PointCloudCallback;

class LidarSubscriber : public rclcpp::Node
{
  public:
    LidarSubscriber();
    void setCallback(PointCloudCallback callback);

  private:
    void lidarCallback(const PointCloud2Msg::SharedPtr msg);

    PointCloudCallback callback_;

    rclcpp::Subscription<PointCloud2Msg>::SharedPtr subscription_;
};

class RosInterface
{
  public:
    RosInterface();
    ~RosInterface();

    void setLidarCallback(PointCloudCallback callback);

  private:
    std::shared_ptr<LidarSubscriber> node_;
};
} // namespace backend
} // namespace dimenvue