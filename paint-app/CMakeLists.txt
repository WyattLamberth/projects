cmake_minimum_required(VERSION 3.10)
project(paint-app)

include(FetchContent)
set(RAYLIB_VERSION 5.5)
FetchContent_Declare(
  raylib 
  URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.zip
  FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

include_directories(${raylib_SOURCE_DIR}/src)
link_directories(${raylib_SOURCE_DIR}/src)

# Set necessary compile definitions and include directories for raylib
add_definitions(-DGRAPHICS_API_OPENGL_33)
add_definitions(-DPLATFORM_DESKTOP)

set(SOURCE_FILES
  main.cpp
)

add_executable(${PROJECT_NAME} paint.cpp)
target_link_libraries(${PROJECT_NAME} raylib)

if (APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
