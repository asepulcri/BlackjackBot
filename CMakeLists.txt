cmake_minimum_required(VERSION 3.5)
project(BlackjackBot)

set(HeaderFiles
	include/Card.h
	include/EnumNames.h
	include/Game.h
	include/HighLowStrategy.h
	include/Player.h
	include/PrintStrings.h
	include/Shoe.h)

set(SourceFiles
	source/Card.cpp
	source/Game.cpp
	source/HighLowStrategy.cpp
	source/Player.cpp
	source/PrintStrings.cpp
	source/Shoe.cpp
	source/main.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MOUDLE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_executable(${PROJECT_NAME} ${SourceFiles})
target_include_directories(${PROJECT_NAME} PRIVATE include)