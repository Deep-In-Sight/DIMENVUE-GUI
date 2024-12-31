#include <RosInterface.h>
#include <pcl_conversions/pcl_conversions.h>

namespace dimenvue
{
namespace backend
{

LidarSubscriber::LidarSubscriber() : Node("dimenvue_ros")
{
    subscription_ = this->create_subscription<PointCloud2Msg>(
        "/colored_cloud", 10, std::bind(&LidarSubscriber::lidarCallback, this, std::placeholders::_1));
}

void LidarSubscriber::setCallback(PointCloudCallback callback)
{
    callback_ = callback;
}

void LidarSubscriber::lidarCallback(const PointCloud2Msg::SharedPtr msg)
{
    if (!callback_)
    {
        return;
    }
    PointCloud::Ptr cloud(new PointCloud);
    pcl::fromROSMsg(*msg, *cloud);
    callback_(cloud);
}

RosInterface::RosInterface()
{
    rclcpp::InitOptions init_options;
    init_options.shutdown_on_signal = false;
    rclcpp::init(0, nullptr, init_options);
    node_ = std::make_shared<LidarSubscriber>();
    std::thread t([this]() { rclcpp::spin(node_); });
    t.detach();
}

RosInterface::~RosInterface()
{
    rclcpp::shutdown();
}

void RosInterface::setLidarCallback(PointCloudCallback callback)
{
    node_->setCallback(callback);
}

} // namespace backend
} // namespace dimenvue