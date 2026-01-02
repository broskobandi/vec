set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.20)
project(vec)

file(GLOB SRC src/*.c)
file(GLOB INC include/*.h)
file(GLOB INC_PRIV src/*.h)

add_library(${PROJECT_NAME} SHARED ${SRC})
add_library(${PROJECT_NAME}-static STATIC ${SRC})
set_target_properties(${PROJECT_NAME}-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME}-static PRIVATE include)

add_executable(test EXCLUDE_FROM_ALL test/test.c)
target_include_directories(test PRIVATE include)

target_compile_options(test PRIVATE -Wall -Wextra -Wunused-result -Wconversion)
