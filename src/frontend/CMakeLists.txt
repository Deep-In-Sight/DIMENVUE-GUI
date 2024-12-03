add_subdirectory(modules)

find_package(
  Qt5 5.15
  COMPONENTS Quick Qml
  REQUIRED)
find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem)
find_package(PCL REQUIRED COMPONENTS common octree)

set(OGRE_LIBS OgreBites OgreRTShaderSystem GLX)
set(OGRE_EXTRA_INCLUDES ${OGRE_INCLUDE_DIRS}/RenderSystems/GL3Plus)
set(QT5_LIBS Qt5::Quick Qt5::Qml qt_imgui_quick)
set(APP_SOURCES
    main.cpp
    QOgreItem.cpp
    OgreEngine.cpp
    CameraController.cpp
    ViewportGrid.cpp
    OverlayDrawer.cpp
    MapVisualizer.cpp)
add_executable(SimpleQtQuickApp ${APP_SOURCES})
target_link_libraries(SimpleQtQuickApp PRIVATE ${OGRE_LIBS} ${QT5_LIBS}
                                               ${PCL_LIBRARIES})
target_include_directories(SimpleQtQuickApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(SimpleQtQuickApp PRIVATE ${OGRE_EXTRA_INCLUDES})
target_include_directories(SimpleQtQuickApp PRIVATE ${PCL_INCLUDE_DIRS})

qt5_add_resources(QML_RESOURCES resource.qrc)
target_sources(SimpleQtQuickApp PRIVATE ${QML_RESOURCES})
set_target_properties(SimpleQtQuickApp PROPERTIES AUTOMOC ON AUTORCC ON)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE ${OGRE_LIBS} ${QT5_LIBS})
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(test PRIVATE ${OGRE_EXTRA_INCLUDES})
