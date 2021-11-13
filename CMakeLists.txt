cmake_minimum_required(VERSION 3.19)

project(network_monitor)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

add_executable(network_monitor ${SOURCES})
target_compile_features(network_monitor
    PRIVATE
        cxx_std_17
)
