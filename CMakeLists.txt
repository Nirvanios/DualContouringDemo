cmake_minimum_required(VERSION 3.15)
set(PROJECT DualContourDemo)
project(${PROJECT})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -fconcepts")
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

include_directories(graphics)
include_directories(DCWrappers)
include_directories(ThirdParty)
include_directories(misc)
include_directories(simpleCSG)
include_directories(VoxParser)
include_directories(VoxParser/Data)
include_directories(${dclib_SOURCE_DIR})

file(GLOB_RECURSE dcwrappers_src "DCWrappers/*.cpp")
file(GLOB_RECURSE graphics_src "graphics/*.cpp")
file(GLOB_RECURSE voxparser_src "VoxParser/*.cpp")
file(GLOB_RECURSE voxparserdata_src "VoxParser/data/*.cpp")
file(GLOB_RECURSE misc_src "misc/*.cpp")
file(GLOB_RECURSE simpleCSG_src "simpleCSG/*.cpp")
file(GLOB_RECURSE octreeDC_src "ThirdParty/DualContouringSample/DualContouringSample/*.cpp")
FOREACH (item ${octreeDC_src})
    IF (${item} MATCHES ".*\/density.cpp" OR ${item} MATCHES ".*\/main.cpp" OR ${item} MATCHES ".*\/glsl_program.cpp")
        LIST(REMOVE_ITEM octreeDC_src ${item})
    ENDIF (${item} MATCHES ".*\/density.cpp" OR ${item} MATCHES ".*\/main.cpp" OR ${item} MATCHES ".*\/glsl_program.cpp")
ENDFOREACH (item)


message(STATUS ${octreeDC_src})

add_compile_definitions(
        GLM_ENABLE_EXPERIMENTAL
)

add_executable(${PROJECT} main.cpp ${dcwrappers_src} ${graphics_src} ${voxparser_src} ${voxparserdata_src} ${octreeDC_src} ${misc_src} ${simpleCSG_src})

target_link_libraries(${PROJECT} geGL::geGL SDL2CPP::SDL2CPP dualcontour)