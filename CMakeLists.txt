cmake_minimum_required(VERSION 3.0.0)
project(ConwayGOL VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_OSX_ARCHITECTURES "arm64")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(OpenGL REQUIRED)

set(INCLUDE_DIRECTORIES
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  src/
  src/grid/
)

set(LINK_LIBRARIES
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

set(SOURCES
  src/main.cc
  src/game.cc
  src/game.h
  src/grid/cell.cc
  src/grid/cell.h
  src/grid/grid.cc
  src/grid/grid.h
  src/grid/coordinates.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

set_property(TARGET ${PROJECT_NAME}
             PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES})

include(CPack)
