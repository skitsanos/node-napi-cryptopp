cmake_minimum_required(VERSION 3.20)

project(demo CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the Node.js headers using node-cmake
include(./node_modules/node-cmake/NodeJS.cmake)
nodejs_init()

# Include the necessary directories
include_directories(
  ${CMAKE_JS_INC}
  "${CMAKE_CURRENT_BINARY_DIR}/node/${NODEJS_VERSION}/include"
  "${CMAKE_HOME_DIRECTORY}/node_modules/@cryptopp/cmake/cryptopp-cmake-build/cryptopp"
  "${CMAKE_HOME_DIRECTORY}/node_modules/node-addon-api"
)

add_subdirectory(${CMAKE_HOME_DIRECTORY}/node_modules/@cryptopp/cmake ${CMAKE_BINARY_DIR}/cryptopp-cmake-build)

# Specify the source files of your addon
file(GLOB SOURCE_FILES
  "./src/*.cpp"
  "./src/*.h"
)

# Create the shared library for your addon
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Set the library file extension to .node
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Link necessary libraries

#target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} cryptopp)
