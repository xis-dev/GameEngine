cmake_minimum_required(VERSION 4.3)
project(AGP_Engine)

set(CMAKE_CXX_STANDARD 20)

# Libraries
include(FetchContent)

FetchContent_Declare(
        box2d
        GIT_TAG v3.2.0
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
)

FetchContent_MakeAvailable(box2d)

add_library(AGP_Engine STATIC src/library.cpp
        src/Core/Engine.cpp
        include/AGP_Engine/Core/Engine.h
        src/Core/Window.cpp
        include/AGP_Engine/Core/Window.h
        src/Graphics/Renderer.cpp
        include/AGP_Engine/Graphics/Renderer.h
        src/Core/Level.cpp
        include/AGP_Engine/Core/Level.h)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_include_directories(${PROJECT_NAME} PRIVATE include/AGP_Engine)

target_link_libraries(${PROJECT_NAME} PRIVATE
        box2d::box2d
)
