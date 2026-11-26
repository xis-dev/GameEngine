cmake_minimum_required(VERSION 3.25)
project(AGP_Xenon)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(../AGP_Engine AGP_Engine)

add_executable(AGP_Xenon src/main.cpp)

#include(tests.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}
)
target_link_libraries(
        ${PROJECT_NAME} PUBLIC

        AGP_Engine
)
