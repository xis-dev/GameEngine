cmake_minimum_required(VERSION 4.3)
project(AGP_Xenon)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(../AGP_Engine AGP_Engine)

add_executable(AGP_Xenon src/main.cpp)

target_link_libraries(
        ${PROJECT_NAME} PUBLIC

        AGP_Engine
)
