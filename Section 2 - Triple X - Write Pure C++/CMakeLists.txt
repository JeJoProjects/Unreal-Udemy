cmake_minimum_required(VERSION 3.6.0)

project(TripleX)


file(GLOB SOURCES
    *.h
    *.hpp
    *.cc
    *.cpp
)


# set the compiler std to build
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# make the single executable using the sources in the current cmake dir
add_executable(${PROJECT_NAME} ${SOURCES})

# set the starting project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

