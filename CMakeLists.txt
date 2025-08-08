cmake_minimum_required(VERSION 3.20)

project(
    eu.dirondin.streamdeck.ram
    VERSION 1.0.2.0
    LANGUAGES "CXX"
)

set(PLUGIN_UUID ${CMAKE_PROJECT_NAME})
set(PLUGIN_DIR_NAME ${PLUGIN_UUID}.sdPlugin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS false)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE STRING "Minimum MacOS version")
if (MSVC)
add_definitions("/Zc:__cplusplus" -DUNICODE=1)
endif()

include(cmake/StreamDeckSDK.cmake)
include(cmake/StreamDeckDeploy.cmake)

add_streamdeck_deploy_targets(${PLUGIN_DIR_NAME})
add_streamdeck_distribute_targets(${PLUGIN_UUID} ${CMAKE_BINARY_DIR}/${PLUGIN_DIR_NAME})
add_dependencies(plugin-pack deploy)
add_dependencies(plugin-validate deploy)

add_subdirectory(src)
add_subdirectory(sdPlugin)

set_default_install_prefix_to_streamdeck_plugin_dir(${PLUGIN_DIR_NAME})
install(
    DIRECTORY ${CMAKE_BINARY_DIR}/${PLUGIN_DIR_NAME}/
    DESTINATION .
)
