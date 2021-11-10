cmake_minimum_required(VERSION 3.22)
project(RT1W)

# openmp
FIND_PACKAGE(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

include_directories(/usr/include)
include_directories(include)

# 1. 链接动态库
# 查找 src/render 目录下的所有源文件
# 并将名称保存到 render_lib_cpp 变量
AUX_SOURCE_DIRECTORY(src/render render_lib_cpp)
add_library(render SHARED ${render_lib_cpp})

add_executable(MAIN src/main.cpp)
# 声明生成可执行文件的时候需要链接动态库
target_link_libraries(MAIN render)