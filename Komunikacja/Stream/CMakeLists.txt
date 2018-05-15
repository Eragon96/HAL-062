
cmake_minimum_required(VERSION 2.8.11)

project(stream)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH "/home/marcin/Qt/QtGstreamer" "/usr/include/gstreamer-1.0")

find_package( Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package( Qt5GStreamer REQUIRED )
find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set  (GST_LIBS "${GST_LIBS} -I/usr/include/gstreamer-1.0 -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0")

include_directories(${QTGSTREAMER_INCLUDES} ${GLIB_INCLUDE_DIRS} "/usr/include/gstreamer-1.0")
add_definitions(${QTGSTREAMER_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${QTGSTREAMER_FLAGS}" )
# Tell CMake to create the helloworld executable
add_executable(stream main.cpp Player.cpp Player.h MainWindow.cpp MainWindow.h)

# Use the Core module from Qt5
target_link_libraries(stream Qt5::Widgets Qt5::Core Qt5::Gui ${QTGSTREAMER_UTILS_LIBRARY} ${QTGSTREAMER_LIBRARY} ${QTGSTREAMER_UI_LIBRARY} -lm -lglib-2.0 -lgobject-2.0 -lgstreamer-1.0 -lgstvideo-1.0)
