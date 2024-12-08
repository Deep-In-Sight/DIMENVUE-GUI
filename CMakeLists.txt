#cmake_minimum_required(VERSION 3.12)
#project(DIMENVUE)
#add_subdirectory(src)

cmake_minimum_required(VERSION 3.5)

project(DIMENVUE LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Threads)

include_directories(src/include)

add_executable(DIMENVUE
    src/main.cpp
    src/qml.qrc
    src/BackendMonitor.cpp
    src/Dimenvue.cpp
    src/DimenvueDB.cpp
    src/SpaceDataModel.cpp
    src/SpaceDataSortProxyModel.cpp
    src/BackendMonitor.h
    src/Dimenvue.h
    src/DimenvueDB.h
    src/Hangul.h
    src/HangulState.h
    src/KoreanCharMaker.h
    src/LanguageTranslationModel.h
    src/SpaceDataModel.h
    src/SpaceDataSortProxyModel.h
    src/backend/mockup/context.cpp
    src/backend/mockup/mapVisualizer.cpp
    src/backend/mockup/scanList.cpp
    src/backend/mockup/scanView.cpp
    src/backend/mockup/sensors.cpp
    src/backend/mockup/setting.cpp
    src/backend/mockup/systemStatus.cpp
)

target_compile_definitions(DIMENVUE
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(DIMENVUE
  PRIVATE Qt5::Core Qt5::Quick
  pthread
)
