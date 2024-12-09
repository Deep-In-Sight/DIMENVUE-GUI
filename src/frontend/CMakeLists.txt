add_subdirectory(modules)

# use c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 5.15 REQUIRED COMPONENTS Quick Qml OpenGL Widgets)
find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem)
find_package(PCL REQUIRED COMPONENTS common octree io)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

set(APP_SOURCES
    main.cpp
    QOgreItem.cpp
    OgreEngine.cpp
    CameraController.cpp
    ViewportGrid.cpp
    OverlayDrawer.cpp
    MapVisualizer.cpp
    OpenGLItem.cpp
    RasterizerRenderer.cpp)

set(APP_LIBS
    OgreBites
    OgreRTShaderSystem
    Qt5::Quick
    Qt5::Qml
    Qt5::OpenGL
    Qt5::Widgets
    qt_imgui_quick
    GLX
    ${PCL_LIBRARIES})

set(APP_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR} ${OGRE_EXTRA_INCLUDES})

add_executable(SimpleQtQuickApp ${APP_SOURCES})
target_link_libraries(SimpleQtQuickApp PRIVATE ${APP_LIBS})
target_include_directories(SimpleQtQuickApp PRIVATE ${APP_INCLUDES})

qt5_add_resources(QML_RESOURCES resource.qrc)
target_sources(SimpleQtQuickApp PRIVATE ${QML_RESOURCES})
set_target_properties(SimpleQtQuickApp PROPERTIES AUTOMOC ON AUTORCC ON)
