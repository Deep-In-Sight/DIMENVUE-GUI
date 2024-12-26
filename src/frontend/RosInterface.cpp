#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

class LidarSubscriber : public rclcpp::Node
{
  public:
    LidarSubscriber() : Node("lidar_subscriber")
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/lidar", 10, std::bind(&LidarSubscriber::lidarCallback, this, std::placeholders::_1));
    }

    void setCallback(std::function<void(const sensor_msgs::msg::PointCloud2::SharedPtr)> callback)
    {
        callback_ = callback;
    }

  private:
    void lidarCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        if (callback_)
        {
            callback_(msg);
        }
    }

    std::function<void(const sensor_msgs::msg::PointCloud2::SharedPtr)> callback_;

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
};

class RosInterface
{
  public:
    RosInterface()
    {
        rclcpp::init(0, nullptr);
        node_ = std::make_shared<LidarSubscriber>();
        std::thread t([this]() { rclcpp::spin(node_); });
        t.detach();
    }

    ~RosInterface()
    {
        rclcpp::shutdown();
    }

    void setLidarCallback(std::function<void(const sensor_msgs::msg::PointCloud2::SharedPtr)> callback)
    {
        node_->setCallback(callback);
    }

  private:
    std::shared_ptr<LidarSubscriber> node_;
};
