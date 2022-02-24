cmake_minimum_required (VERSION 3.13)

project (exhydro)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Locate custom Find*.cmake files
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# Used in custom Find*.cmake files
include(FindPackageHandleStandardArgs)

# Set search paths
string(REPLACE ":" ";" LIBRARY_DIRS "$ENV{LD_LIBRARY_PATH}")
list(APPEND CMAKE_LIBRARY_PATH ${LIBRARY_DIRS})

string(REPLACE ":" ";" INCLUDE_DIRS "$ENV{C_INCLUDE_PATH}")
list(APPEND CMAKE_INCLUDE_PATH ${INCLUDE_DIRS})

string(REPLACE ":" ";" INCLUDE_DIRS "$ENV{CPLUS_INCLUDE_PATH}")
list(APPEND CMAKE_INCLUDE_PATH ${INCLUDE_DIRS})


#add_executable(exhydro exhydro.cpp Mesh.cpp ScalarMonotonic.cpp PredictorCorrector.cpp)

add_subdirectory(src)
add_executable(exhydro ${PROJECT_SOURCE_DIR}/src/exhydro.cpp)

target_link_libraries(exhydro PRIVATE libexo)

# ------------------------------------------------------------------------------
# Find dependencies
# ------------------------------------------------------------------------------
# Locate yaml-cpp
find_package(YamlCpp REQUIRED)
target_include_directories(libexo PUBLIC ${YamlCpp_INCLUDES})
target_link_libraries(libexo PRIVATE ${YamlCpp_LIBRARIES})
