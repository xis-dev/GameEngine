cmake_minimum_required(VERSION 4.3)
project(AGP_Engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Libraries
include(FetchContent)

FetchContent_Declare(
        box2d
        GIT_TAG v3.2.0
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
)

FetchContent_MakeAvailable(box2d)

FetchContent_Declare(
        SDL3
        GIT_TAG release-3.4.18
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_SHALLOW TRUE
)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)   # no SDL3.dll / libSDL3.dylib to ship
set(SDL_STATIC ON  CACHE BOOL "" FORCE)   # link SDL3 into our executable
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL3)

set(GLAD_DIR ${PROJECT_SOURCE_DIR}/external_deps/glad)

set(DEPS_DIRS
        ${GLAD_DIR})

set(DEPS_SOURCES
        ${GLAD_DIR}/glad.c)

set(PROJECT_SOURCES
        src/Core/Engine.cpp
        src/Core/Window.cpp
        src/Graphics/Renderer.cpp
        src/Core/Level.cpp
        src/Resources/ResourceManager.cpp
        src/Resources/Shader.cpp
        include/AGP_Engine/Resources/Shader.h)

add_library(AGP_Engine STATIC
        ${DEPS_SOURCES}
        ${PROJECT_SOURCES})

target_compile_definitions(AGP_Engine PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(AGP_Engine PUBLIC
        include
        ${DEPS_DIRS}
)

target_include_directories(AGP_Engine PRIVATE include/AGP_Engine)

target_link_libraries(AGP_Engine PRIVATE
        box2d::box2d
        SDL3::SDL3-static
)
