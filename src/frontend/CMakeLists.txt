find_package(
  Qt5 5.15
  COMPONENTS Quick Qml
  REQUIRED)
find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem)

set(OGRE_LIBS OgreBites OgreRTShaderSystem RenderSystem_GL3Plus)
set(OGRE_EXTRA_INCLUDES ${OGRE_INCLUDE_DIRS}/RenderSystems/GL3Plus)
set(QT5_LIBS Qt5::Quick Qt5::Qml)

add_executable(SimpleQtQuickApp main.cpp QOgreItem.cpp OgreEngine.cpp
                                CameraController.cpp)
target_link_libraries(SimpleQtQuickApp PRIVATE ${OGRE_LIBS} ${QT5_LIBS})
target_include_directories(SimpleQtQuickApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(SimpleQtQuickApp PRIVATE ${OGRE_EXTRA_INCLUDES})

qt5_add_resources(QML_RESOURCES resource.qrc)
target_sources(SimpleQtQuickApp PRIVATE ${QML_RESOURCES})
set_target_properties(SimpleQtQuickApp PROPERTIES AUTOMOC ON AUTORCC ON)
