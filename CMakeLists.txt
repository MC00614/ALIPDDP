cmake_minimum_required(VERSION 3.12)
project(alipddp)

# find_package(Python3 COMPONENTS Development REQUIRED)
# find_package(OpenMP REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/alipddp/
    ${CMAKE_SOURCE_DIR}/problem_maker/
    ${CMAKE_SOURCE_DIR}/eigen/
    # ${CMAKE_SOURCE_DIR}/matplotlib-cpp/
    # ${Python3_INCLUDE_DIRS}
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wextra -Wpedantic -DDEBUG -fno-inline -fno-omit-frame-pointer")
    # fsanitize=address is not compatible with shared pointer
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wextra -Wpedantic -DDEBUG -fsanitize=address -fno-omit-frame-pointer")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

add_library(alipddp_library STATIC alipddp/alipddp/alipddp.cpp)
target_include_directories(alipddp_library PRIVATE ${INCLUDE_DIRS})

option(BUILD_EXAMPLE "Build example binaries" OFF)
if (BUILD_EXAMPLE)
foreach(EXAMPLE
    minwork_double_integrator
    rocket_3d
    rocket_2d
    point_mass_3d_basic
    point_mass_3d_simple
    # rocket_3d_scaled
)
    add_executable(${EXAMPLE} problem_examples/${EXAMPLE}.cpp)
    target_include_directories(${EXAMPLE} PRIVATE ${INCLUDE_DIRS})
    target_compile_options(${EXAMPLE} PRIVATE -O3)
    target_link_libraries(${EXAMPLE} PRIVATE alipddp_library)
    # target_link_libraries(${EXAMPLE} PRIVATE ${Python3_LIBRARIES} alipddp_library)
endforeach()
endif()

option(BUILD_PYTHON_BINDINGS "Build Python bindings using pybind11" OFF)
if(BUILD_PYTHON_BINDINGS)
    find_package(pybind11 QUIET)
    if (pybind11_FOUND)
        message(STATUS "Found system pybind11: using installed version.")
        add_subdirectory(bindings)
    elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/pybind11/CMakeLists.txt")
        message(STATUS "Using local pybind11 subdirectory.")
        add_subdirectory(pybind11)
        add_subdirectory(bindings)
    else()
        message(STATUS "pybind11 not found, skipping Python bindings.")
    endif()
endif()
