cmake_minimum_required(VERSION 3.12)
project(fltk-dockable-group)

find_package(FLTK CONFIG REQUIRED)
add_library(Fl_Dock src/dock_gp.cxx src/dropwin.cxx)
target_include_directories(Fl_Dock PUBLIC include)
target_link_libraries(Fl_Dock PUBLIC fltk)

option(FL_DOCK_BUILD_EXAMPLE "Builds the dockable group example" ON)

if (${FL_DOCK_BUILD_EXAMPLE})
    add_executable(test example/test.cxx example/drag_btn.cxx example/toolgrp.cxx example/toolwin.cxx)
    target_link_libraries(test PUBLIC Fl_Dock)
endif()
