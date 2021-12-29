# CMakeList.txt : CMake project for OpenCV Sample Project, include source and define
# project specific logic here.

# Find_package did not work for me without specifying the path to the .cmake files
# Note with this since the configuration is in Release for this example that the
# CMakeSettings should be configured to Release and not RelwithDbInfo otherwise
# A linker error will occur

cmake_minimum_required (VERSION 3.8)

project(WebcamFilters LANGUAGES CXX)

# Note LIBS_PATH is my env var to where all my libraries are located. also bin dlls
# are mapped to my PATH as well.
set(OpenCV_DIR $ENV{LIBS_PATH}/opencv-master/out/install/x64-Release)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_LIB_DIR})

# Add source to this project's executable.
add_executable(WebcamFilters "source.cpp")

target_link_libraries(WebcamFilters ${OpenCV_LIBS})