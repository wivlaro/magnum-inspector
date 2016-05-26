
#To use, add something like this to your 
# include(path/to/inspector/inspector.cmake)
# add_executable(fooapp ... ${MAGNUMINSPECTOR_SOURCES})
# target_link_libraries(fooapp ... ${MAGNUMINSPECTOR_LIBRARIES})

find_package(PkgConfig REQUIRED)

message("Found pkgconfig")
pkg_check_modules(GTK3 REQUIRED gtk+-3.0 gtkmm-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

set(MAGNUMINSPECTOR_SOURCE_PREFIX ${CMAKE_CURRENT_LIST_DIR})
set(MAGNUMINSPECTOR_SOURCES
	${MAGNUMINSPECTOR_SOURCE_PREFIX}/GtkAbstractInspector.cpp
	${MAGNUMINSPECTOR_SOURCE_PREFIX}/GtkChildPopulator.cpp
	${MAGNUMINSPECTOR_SOURCE_PREFIX}/GtkInspectionField.cpp
	${MAGNUMINSPECTOR_SOURCE_PREFIX}/GtkMatrixWidget.cpp
	${MAGNUMINSPECTOR_SOURCE_PREFIX}/GtkObjectFrame.cpp
	${MAGNUMINSPECTOR_SOURCE_PREFIX}/GtkInspector.cpp
	${MAGNUMINSPECTOR_SOURCE_PREFIX}/Inspectable.cpp
	${MAGNUMINSPECTOR_SOURCE_PREFIX}/Inspector.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")

if(Boost_FOUND)
	add_definitions(-DMAGNUMINSPECTOR_BOOST)
endif()

set(MAGNUMINSPECTOR_LIBRARIES ${GTK3_LIBRARIES})

add_definitions(-DMAGNUMINSPECTOR)
