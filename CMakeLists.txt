cmake_minimum_required (VERSION 3.0)

project (exhydro)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

#add_executable(exhydro exhydro.cpp Mesh.cpp ScalarMonotonic.cpp PredictorCorrector.cpp)

add_subdirectory(src)
add_executable(exhydro ${PROJECT_SOURCE_DIR}/src/exhydro.cpp)

target_link_libraries(exhydro PRIVATE libexo)
