find_package(Threads REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED COMPONENTS common)

set(MOCKUP_SRCS
    context.cpp
    scanList.cpp
    scanView.cpp
    sensors.cpp
    setting.cpp
    systemStatus.cpp
    mapVisualizer.cpp
    RosInterface.cpp)

set(MOCKUP_INCLUDES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PCL_INCLUDE_DIRS}
    )


add_library(mockup_backend STATIC ${MOCKUP_SRCS})
target_include_directories(mockup_backend
                           PUBLIC ${MOCKUP_INCLUDES})
target_link_libraries(mockup_backend ${PCL_LIBRARIES})
# target_link_libraries(mockup_backend PUBLIC Threads::Threads rclcpp::rclcpp
# sensor_msgs::sensor_msgs_library)
ament_target_dependencies(mockup_backend Threads rclcpp sensor_msgs pcl_conversions)
