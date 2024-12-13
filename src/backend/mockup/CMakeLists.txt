find_package(Threads REQUIRED)

set(MOCKUP_SRCS
    context.cpp
    scanList.cpp
    scanView.cpp
    sensors.cpp
    setting.cpp
    systemStatus.cpp
    mapVisualizer.cpp)
add_library(mockup_backend STATIC ${MOCKUP_SRCS})
target_include_directories(mockup_backend
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_include_directories(mockup_backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mockup_backend PUBLIC Threads::Threads)
