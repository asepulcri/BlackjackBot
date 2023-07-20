cmake_minimum_required(VERSION 3.24)
project(BlackjackBot)

set(CMAKE_CXX_STANDARD 23)

add_library(BlackjackBot STATIC
	source/card.cpp
	source/player.cpp
	source/shoe.cpp

	include/card.h
	include/player.h
	include/shoe.h
 )

add_executable(BlackjackBotApp
	source/main.cpp

	source/card.cpp
	source/player.cpp
	source/shoe.cpp

	include/card.h
	include/player.h
	include/shoe.h)