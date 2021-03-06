cmake_minimum_required(VERSION 2.8)

project(Ageron)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# SDL2, SDL2/SDL2_Image, SDL2/SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} 
					${SDL2IMAGE_INCLUDE_DIR}
					${SDL2TTF_INCLUDE_DIR})

# Ageron
include_directories(src/)
file(GLOB SOURCES src/*.cpp src/*.c)
file(GLOB HEADERS src/*.hpp src/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} 
					  ${SDL2_LIBRARY} 
					  ${SDL2IMAGE_LIBRARY}
					  ${SDL2TTF_LIBRARY})
