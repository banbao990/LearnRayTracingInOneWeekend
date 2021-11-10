cmake_minimum_required(VERSION 3.22)
project(RT1W)

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