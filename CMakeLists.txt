cmake_minimum_required(VERSION 3.12)

project(ClayEngineDemo)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Collect all source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Add ClayEngine as a subdirectory and link to it
add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/clay clay_build)
target_link_libraries(${PROJECT_NAME} PRIVATE ClayEngine)

# Include project-specific directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)
