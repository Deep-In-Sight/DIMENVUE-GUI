set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
  Qt5
  COMPONENTS Core Quick
  REQUIRED)
find_package(Threads)

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

add_executable(TestBackend test.cpp)
target_include_directories(TestBackend PRIVATE ${DIMENVUE_INCLUDES})
target_link_libraries(TestBackend PRIVATE mockup_backend Threads::Threads)
