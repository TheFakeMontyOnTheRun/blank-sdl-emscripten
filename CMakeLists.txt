cmake_minimum_required(VERSION 3.11)
project(blank)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_find")

include_directories(
		${SDL2_INCLUDE_DIR}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(SDL2 REQUIRED)

add_executable(blank
		main.cpp
		)

include(FindPkgConfig)

target_include_directories(blank PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(blank LINK_PUBLIC ${SDL2_LIBRARY} m)

