cmake_minimum_required(VERSION 3.10)
project(Projekt)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projekt main.cpp Game.cpp Game.h Node.cpp Node.h Grid.cpp Grid.h Pathfinder.cpp Pathfinder.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(Projekt ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
