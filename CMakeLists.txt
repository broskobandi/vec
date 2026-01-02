set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED 23)
set(CMAKE_C_EXTENSIONS OFF)

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

add_executable(test EXCLUDE_FROM_ALL test/test.c ${SRC})
target_include_directories(test PRIVATE include)

target_compile_options(test PRIVATE -Wall -Wextra -Wunused-result -Wconversion)
