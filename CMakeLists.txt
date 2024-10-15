cmake_minimum_required(VERSION 3.16)

project(SlaughteringAlarmPLC VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

find_library(SNAP7 snap7 HINTS ${CMAKE_CURRENT_SOURCE_DIR}/lib)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appSlaughteringAlarmPLC
    main.cpp
    snap7.h snap7.cpp
    plc_siemens.h plc_siemens.cpp
    alarmsconfig.h alarmsconfig.cpp
    alarmconfigitem.h alarmconfigitem.cpp
)

qt_add_qml_module(appSlaughteringAlarmPLC
    URI SlaughteringAlarmPLC
    VERSION 1.0
    RESOURCES
        img/logo.png
    QML_FILES
        Main.qml
        SOURCES alarmlistmodel.h alarmlistmodel.cpp
        SOURCES alarmhistoryitem.h alarmhistoryitem.cpp
        SOURCES alarmhistorylistmodel.h alarmhistorylistmodel.cpp
)

qt_add_resources(appSlaughteringAlarmPLC "alarms_config"
    FILES
        Alarms.csv
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSlaughteringAlarmPLC PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSlaughteringAlarmPLC
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSlaughteringAlarmPLC
    PRIVATE Qt6::Quick
    ${SNAP7}
)

include(GNUInstallDirs)
install(TARGETS appSlaughteringAlarmPLC
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
