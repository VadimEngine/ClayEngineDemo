cmake_minimum_required(VERSION 3.12)

project(ClayEngineDemo)
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -c")
set(BUILD_MODE "x64" CACHE STRING "Build mode: x64 or Win32")

# Collect all source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link ClayEngine
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/build/Debug/ClayEngine.lib
)

# Include ClayEngine headers
target_include_directories(${PROJECT_NAME} PRIVATE
    # source code
    ${CMAKE_SOURCE_DIR}/src
    # ClayEngine
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/include
    # third party
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/ThirdParty/assimp/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/ThirdParty/freetype/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/ThirdParty/glew-cmake/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/ThirdParty/glfw/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/ThirdParty/glm
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/ThirdParty/glm/backends
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/ThirdParty/imgui
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/ThirdParty/imgui/backends
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/ThirdParty/openal-soft/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/ThirdParty/libsndfile/include
    ${CMAKE_SOURCE_DIR}/ThirdParty/clay/ThirdParty/soil/inc/SOIL
)