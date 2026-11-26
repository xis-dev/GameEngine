FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.16.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(${PROJECT_NAME}
        tests/components.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Catch2::Catch2WithMain
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -fsanitize=address,undefined)
target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)

include(CTest)
include(Catch)

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
catch_discover_tests(${PROJECT_NAME})

