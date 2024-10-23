set(MOCKUP_SRCS context.cpp scanList.cpp scanView.cpp sensors.cpp setting.cpp
                systemStatus.cpp)
add_library(mockup_backend STATIC ${MOCKUP_SRCS})
target_include_directories(mockup_backend
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_include_directories(mockup_backend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
