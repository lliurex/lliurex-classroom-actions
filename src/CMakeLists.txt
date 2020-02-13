
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(APP_NAME "llx-classroom-actions")

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(KF5 REQUIRED COMPONENTS Config)

add_executable(${APP_NAME} main.cpp controlwindow.cpp classroomaction.cpp)

target_link_libraries(${APP_NAME} Qt5::Core Qt5::Widgets KF5::ConfigCore)

install(TARGETS ${APP_NAME} RUNTIME DESTINATION bin)
