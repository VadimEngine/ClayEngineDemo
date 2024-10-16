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
    ${CMAKE_SOURCE_DIR}/../ClayEngine/build/Debug/ClayEngine.lib
)

# Include ClayEngine headers
target_include_directories(${PROJECT_NAME} PRIVATE
    # source code
    ${CMAKE_SOURCE_DIR}/src
    # ClayEngine
    ${CMAKE_SOURCE_DIR}/../ClayEngine/include
    # third party
    ${CMAKE_SOURCE_DIR}/../ClayEngine/ThirdParty/assimp/include
    ${CMAKE_SOURCE_DIR}/../ClayEngine/ThirdParty/freetype/include
    ${CMAKE_SOURCE_DIR}/../ClayEngine/ThirdParty/GLEW/include
    ${CMAKE_SOURCE_DIR}/../ClayEngine/ThirdParty/GLFW/include
    ${CMAKE_SOURCE_DIR}/../ClayEngine/ThirdParty/glm
    ${CMAKE_SOURCE_DIR}/../ClayEngine/ThirdParty/imgui
    ${CMAKE_SOURCE_DIR}/../ClayEngine/ThirdParty/openAL/include
    ${CMAKE_SOURCE_DIR}/../ClayEngine/ThirdParty/sndfile/include
    ${CMAKE_SOURCE_DIR}/../ClayEngine/ThirdParty/SOIL/include
)