QT += quick virtualkeyboard

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES +=                      \
        QT_DEPRECATED_WARNINGS  \
        _GLIBCXX_USE_NANOSLEEP

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        BackendMonitor.cpp \
        Dimenvue.cpp \
        DimenvueDB.cpp \
        SpaceDataModel.cpp \
        SpaceDataSortProxyModel.cpp \
        backend/mockup/context.cpp \
        backend/mockup/mapVisualizer.cpp \
        backend/mockup/scanList.cpp \
        backend/mockup/scanView.cpp \
        backend/mockup/sensors.cpp \
        backend/mockup/setting.cpp \
        backend/mockup/systemStatus.cpp \
        main.cpp

INCLUDEPATH += \
        include

LIBS += -lpthread

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    BackendMonitor.h \
    Dimenvue.h \
    DimenvueDB.h \
    Hangul.h \
    HangulState.h \
    KoreanCharMaker.h \
    LanguageTranslationModel.h \
    SpaceDataModel.h \
    SpaceDataSortProxyModel.h \
    include/context.hpp \
    include/mapVisualizer.hpp \
    include/scanList.hpp \
    include/scanView.hpp \
    include/sensors.hpp \
    include/setting.hpp \
    include/systemStatus.hpp

DISTFILES += \
    resources/localization/Dimenvue_en-us.ts \
    resources/localization/Dimenvue_ko.ts

TRANSLATIONS += \
    resources/localization/Dimenvue_ko.ts \
    resources/localization/Dimenvue_en-us.ts
