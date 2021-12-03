cmake_minimum_required(VERSION 3.19)

project(network_monitor)

set(CMAKE_CXX_STANDARD 17)

# Dependencies
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conaninfo.txt)
    list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")
endif()
find_package(Boost 1.74 REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

add_executable(network_monitor ${SOURCES})
target_link_libraries(network_monitor
    PRIVATE
        Boost::Boost
        OpenSSL::OpenSSL
)
target_compile_features(network_monitor
    PRIVATE
        cxx_std_17
)
