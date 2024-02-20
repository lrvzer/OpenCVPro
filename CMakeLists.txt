cmake_minimum_required(VERSION 3.20)

project(OpenCVPro)

set(CMAKE_CXX_STANDARD 17)
if (MSVC)
    set(OpenCV_DIR "D:\\3rdparty\\opencv\\x64\\vc16\\lib")
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()
# find_package(Boost REQUIRED)
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS         = ${OpenCV_LIBS}")

# 包含opencv相关头文件
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB_RECURSE CURRENT_DIR_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(FILE ${CURRENT_DIR_FILES})
    get_filename_component(FILENAME_WITHOUT_EXTENSION ${FILE} NAME_WE)
    add_executable(${FILENAME_WITHOUT_EXTENSION} ${FILE})
    target_link_libraries(${FILENAME_WITHOUT_EXTENSION}  ${OpenCV_LIBS})
endforeach()