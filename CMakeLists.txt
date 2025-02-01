cmake_minimum_required(VERSION 3.14)

project(eu.dirondin.streamdeck.ram VERSION 1.0)

include("cmake/StreamDeckSDK.cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CSS_FLAGS_DEBUG "-g")
set(CMAKE_CSS_FLAGS_DEBUG "-O3")
set(CXX_STANDARD_REQUIRED true)
if (MSVC)
add_definitions("/Zc:__cplusplus" -DUNICODE=1)
endif()

include_directories("${CMAKE_SOURCE_DIR}/src")

set(
  SOURCES
  src/main.cpp
  src/StreamDeckPlugin.cpp
  src/ThreadTimer.cpp
)

set(
  LIBS
  StreamDeckSDK
)

if (APPLE)
  list(APPEND SOURCES src/mac/MacPlatformUtils.cpp)
elseif (WIN32)
  list(APPEND SOURCES src/win/WinPlatformUtils.cpp)
endif()

add_executable(
  ram
  ${SOURCES}
)
target_link_libraries(ram ${LIBS})

# Build plugin

add_custom_target(plugin
  DEPENDS ram
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/dist/${CMAKE_PROJECT_NAME}.sdPlugin"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/resources" "${CMAKE_SOURCE_DIR}/dist/${CMAKE_PROJECT_NAME}.sdPlugin"
  COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:ram>" "${CMAKE_SOURCE_DIR}/dist/${CMAKE_PROJECT_NAME}.sdPlugin/"
)
