aux_source_directory(. LIB_SRC_LIST)
add_library(MathFunctions ${LIB_SRC_LIST}) # 默认生成静态库，等价于add_library(MathFunctions STATIC MathFunctions.cpp)

message("[CMake][Math] Begin to install")
install(TARGETS MathFunctions DESTINATION Math/bin)
install(FILES MathFunction.h DESTINATION Math/include)

#add_library(MathFunctions STATIC ${LIB_SRC_LIST}) # 生成静态库
#add_library(MathFunctions SHARED ${LIB_SRC_LIST}) # 生成动态库或共享库