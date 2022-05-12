cmake_minimum_required(VERSION 3.0.0)
project(ConwayGOL VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")

find_library(SDL2_LIBRARY NAME SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(ConwayGOL ${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

set(SOURCES
  src/main.cc
  src/game.cc
)

add_executable(ConwayGOL ${SOURCES})

target_link_libraries(ConwayGOL ${SDL2_LIBRARY} ${OPENGL_LIBRARIES})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

include(CPack)
