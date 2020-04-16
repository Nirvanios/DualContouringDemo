cmake_minimum_required(VERSION 3.15)
set(PROJECT DualContourDemo)
project(${PROJECT})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
include(FetchContent)

set(SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/SDL2/lib/cmake/SDL2)

find_package(SDL2 CONFIG REQUIRED)

FetchContent_Declare(SDL2CPP GIT_REPOSITORY https://github.com/dormon/SDL2CPP.git)
FetchContent_Declare(geGL GIT_REPOSITORY https://github.com/dormon/geGL.git)
FetchContent_Declare(DClib GIT_REPOSITORY https://github.com/salvipeter/dual-contouring.git)

FetchContent_GetProperties(SDL2CPP)
if (NOT SDL2CPP_POPULATED)
    FetchContent_Populate(SDL2CPP)
    add_subdirectory(${sdl2cpp_SOURCE_DIR} ${sdl2cpp_BINARY_DIR})
endif ()

FetchContent_GetProperties(geGL)
if (NOT geGL_POPULATED)
    FetchContent_Populate(geGL)
    add_subdirectory(${gegl_SOURCE_DIR} ${gegl_BINARY_DIR})
endif ()

FetchContent_GetProperties(DCLib)
if (NOT DClib_POPULATED)
    FetchContent_Populate(DCLib)
    add_subdirectory(${dclib_SOURCE_DIR} ${dclib_BINARY_DIR})
endif ()

include_directories(ThirdParty)
include_directories(./)
include_directories(${dclib_SOURCE_DIR})

add_compile_definitions(
        GLM_ENABLE_EXPERIMENTAL
)

add_executable(${PROJECT} main.cpp operations.cpp shapes.cpp Utils.cpp )

target_link_libraries(${PROJECT} geGL::geGL SDL2CPP::SDL2CPP dualcontour)