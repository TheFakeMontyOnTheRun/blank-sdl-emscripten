cmake_minimum_required(VERSION 3.11)
project(blank)

set(CMAKE_C_STANDARD 90)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_find")

include_directories(
		${SDL2_INCLUDE_DIR}
)

include_directories(base3d/include)
include_directories(common/include)
include_directories(menu/include)
include_directories(SoundSystem)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -DSDLSW -std=c90 -W -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DSDLSW -std=c++98 -W -Wall")

find_package(SDL2 REQUIRED)

add_executable(blank
		menu/src/MainMenu.cpp
		menu/src/Interrogation.cpp
        menu/src/HelpScreen.cpp
		menu/src/CreditsScreen.cpp
        menu/src/Main.cpp
		menu/src/Engine.cpp
		base3d/src/SDLVersion/CSDL2Renderer.cpp
		base3d/src/Globals.cpp
		base3d/src/LoadBitmap.cpp
		base3d/src/CRenderer.cpp
		base3d/src/FixP.cpp
		base3d/src/CRenderer_Rasterization.cpp
		base3d/src/CPackedFileReader.cpp
        menu/src/UI.cpp
		)


include(FindPkgConfig)

target_include_directories(blank PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(blank LINK_PUBLIC ${SDL2_LIBRARY} m)

