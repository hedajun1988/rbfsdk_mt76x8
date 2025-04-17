cmake_minimum_required(VERSION 2.8)
project(rbfsdk)


set(CMAKE_SYSTEM_NAME linux)
set(CMAKE_SYSTEM_PROCESSOR mips)


set(CMAKE_C_COMPILER mipsel-openwrt-linux-gcc)
set(CMAKE_CXX_COMPILER mipsel-openwrt-linux-g++)


add_definitions(-DCONFIG_RPC_ENABLE)

link_directories(${PROJECT_SOURCE_DIR}/platform/linux/mips_mt76x8)
aux_source_directory(${PROJECT_SOURCE_DIR}/platform/linux/test SRC_LIST)
add_executable(rbftest ${SRC_LIST})


include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/test
)

target_link_libraries(rbftest 
    rbf
    pthread
    rt
)
