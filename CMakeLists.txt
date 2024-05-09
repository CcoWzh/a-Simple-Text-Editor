CMAKE_MINIMUM_REQUIRED(VERSION 3.23)
PROJECT(fltk_demo)

SET(CMAKE_CXX_STANDARD 11)

# 可执行程序名称，下面统一使用
SET(my_app_name fltk_demo)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

link_directories(${PROJECT_SOURCE_DIR}/lib)
# 指定头文件搜索路径
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

# 指定头文件查找目录
# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 将src下面的所有头文件路径保存至 all_head_files 数组变量中
# 将src下面的所有源文件路径保存至 all_source_files 数组变量中
FILE(GLOB_RECURSE all_source_files "src/*.cpp" "src/*.c")
FILE(GLOB_RECURSE all_head_files "src/*.hpp" "src*.h")


# LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/lib")
ADD_EXECUTABLE(
            ${my_app_name}
            WIN32 # Windows 非命令行程序
            ${all_head_files}
            ${all_source_files}
             )
TARGET_LINK_LIBRARIES(
            ${my_app_name}
            PRIVATE
            fltk # 链接的静态库名称，这里只需要写fltk，在运行时自动查找.a/.lib
            )
