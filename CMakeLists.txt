cmake_minimum_required(VERSION 3.22)

project(nBody VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS -O2)

#find_package(OpenMP)
#f(OpenMP_CXX_FOUND)
#    target_link_libraries(MyTarget PUBLIC OpenMP::OpenMP_CXX)
#endif()

# Ensure cmake can find conan libraries
set(Eigen3_DIR ${CMAKE_BINARY_DIR})
set(Catch2_DIR ${CMAKE_BINARY_DIR})

# Make executables appear in build, not build/src
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})



# Build application
add_subdirectory(app)

# Build library
add_subdirectory(src)

# Build tests
enable_testing()
add_subdirectory(test)