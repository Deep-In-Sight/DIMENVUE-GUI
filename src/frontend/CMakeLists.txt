add_subdirectory(modules)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
  Qt5
  COMPONENTS Core Quick Qml
  REQUIRED)
find_package(Threads)
find_package(PCL REQUIRED COMPONENTS common)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(DIMENVUE_SRCS
    main.cpp
    qml.qrc
    BackendMonitor.cpp
    Dimenvue.cpp
    DimenvueDB.cpp
    SpaceDataModel.cpp
    SpaceDataSortProxyModel.cpp
    BackendMonitor.h
    Dimenvue.h
    DimenvueDB.h
    Hangul.h
    HangulState.h
    KoreanCharMaker.h
    LanguageTranslationModel.h
    SpaceDataModel.h
    SpaceDataSortProxyModel.h)

set(DIMENVUE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}
                      ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_executable(DIMENVUE ${DIMENVUE_SRCS})

target_compile_definitions(
  DIMENVUE
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(DIMENVUE PRIVATE Qt5::Core Qt5::Quick Threads::Threads
                                       mockup_backend)

set(APP_SOURCES test_pcd.cpp OverlayDrawer.cpp global.cpp test_pcd.qrc)

set(APP_LIBS
    OpenGL::GL
    Qt5::Quick
    Qt5::Qml
    qt_imgui_quick
    GLX
    GLEW::GLEW
    ${PCL_LIBRARIES})

set(APP_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR} ${OGRE_EXTRA_INCLUDES})

add_executable(SimpleQtQuickApp ${APP_SOURCES})
target_link_libraries(SimpleQtQuickApp PRIVATE ${APP_LIBS} ComputeRasterizerLib)
target_include_directories(SimpleQtQuickApp PRIVATE ${APP_INCLUDES})

target_sources(SimpleQtQuickApp PRIVATE ${QML_RESOURCES})
set_target_properties(SimpleQtQuickApp PROPERTIES AUTOMOC ON AUTORCC ON)
