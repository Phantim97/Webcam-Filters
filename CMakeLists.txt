cmake_minimum_required(VERSION 3.8)

project(WebcamFilters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

# Configure FetchContent to download OpenCV
FetchContent_Declare(
		opencv
		GIT_REPOSITORY https://github.com/opencv/opencv.git
		GIT_TAG master
)

# Download OpenCV only if it's not already downloaded
FetchContent_GetProperties(opencv)
if(NOT opencv_POPULATED)
	FetchContent_Populate(opencv)
endif()

include_directories(${opencv_SOURCE_DIR}/include ${opencv_BINARY_DIR}/include)

add_executable(WebcamFilters source.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(WebcamFilters ${OpenCV_LIBS})
