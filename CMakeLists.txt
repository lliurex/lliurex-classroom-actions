cmake_minimum_required(VERSION 3.0)
project(lliurex-classroom-actions)

add_subdirectory(src)

install(FILES llx-classroom-actions.desktop DESTINATION etc/xdg/autostart/)