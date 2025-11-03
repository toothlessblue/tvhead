cmake_minimum_required(VERSION 3.29.4)

project("tvhead")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE $ENV{CMAKE_BUILD_TYPE})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

message(${CMAKE_BUILD_TYPE})
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    message("Building in debug mode!")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -g")
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    message("Building in release mode!")
    set(CMAKE_CXX_FLAGS "-O3")
endif()

add_executable(tvhead 
    src/main.cpp 
    src/gl-init.cpp
    src/render-item.cpp
    src/render-list.cpp

    lib/led-matrix.cc
    lib/framebuffer.cc
    lib/gpio.cc
    lib/graphics.cc
    lib/hardware-mapping.c
    lib/multiplex-mappers.cc
    lib/options-initialize.cc
    lib/pixel-mapper.cc
    lib/thread.cc
    lib/bdf-font.cc
)

target_include_directories(tvhead PRIVATE /usr/include/libdrm)
target_include_directories(tvhead PRIVATE /usr/include/GLES2)
target_link_libraries(tvhead -ldrm -lgbm -lEGL -lGLESv2)

target_include_directories(tvhead PRIVATE include)
target_include_directories(tvhead PRIVATE lib)
