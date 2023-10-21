message("[CMake] Welcom")
cmake_minimum_required(VERSION 3.6) # 指定CMake最小版本
project(Demo) # 设置项目名称

set(Demo_VERSION_MAJOR 1)
set(Demo_VERSION_MINOR 0)

set(CMAKE_BUILD_TYPE "Debug") # 设定编译类型为Debug模式
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb") # Debug模式开启gdb模式
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

message(DEBUG "[CMake] Begin to configure file")
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/include/config.h"
) # 加入一个配置头文件，用于处理CMake对源码的设置
include_directories("${PROJECT_BINARY_DIR}/include/")

option(USE_MYMATH "Use provided math implementation" ON) # 设置为ON或者OFF
if(USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/Math")
    add_subdirectory(Math) # 添加子目录Math
    set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(USE_MYMATH)

aux_source_directory(. SRC_LIST) # 查找当前目录下的所有源文件并将名称保存在变量SRC_LIST中
add_executable(Demo ${SRC_LIST}) # 生成可执行文件
target_link_libraries(Demo ${EXTRA_LIBS})

message("[CMake] Begin to install")
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install")
install(TARGETS Demo DESTINATION bin) # 指定生成的目标文件安装在"${CMAKE_INSTALL_PREFIX}/bin"目录下
install(FILES "${PROJECT_BINARY_DIR}/include/config.h" DESTINATION include) # 指定头文件安装在"${CMAKE_INSTALL_PREFIX}/include"目录下

enable_testing() # 启用测试
macro(do_test arg1 arg2 result)
    add_test(test_${arg1}_${arg2} Demo ${arg1} ${arg2})
    set_tests_properties(test_${arg1}_${arg2} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(do_test arg1 arg2 result)
do_test(2 10 "=1024")
do_test(5 2 "=25")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
include(CPack)

#file(GLOB SRC_LIST "*.cpp" "protocol/*.cpp")
#add_library(demo ${SRC_LIST})
# 或者
#file(GLOB SRC_LIST "*.cpp")
#file(GLOB SRC_PROTOCOL_LIST "protocol/*.cpp")
#add_library(demo ${SRC_LIST} ${SRC_PROTOCOL_LIST})
# 或者
#aux_source_directory(. SRC_LIST)
#aux_source_directory(protocol SRC_PROTOCOL_LIST)
#add_library(demo ${SRC_LIST} ${SRC_PROTOCOL_LIST})