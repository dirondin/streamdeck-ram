cmake_minimum_required(VERSION 3.20)

project(
    eu.dirondin.streamdeck.ram
    VERSION 1.0.1.0
    LANGUAGES "CXX"
)

set(PLUGIN_UUID ${CMAKE_PROJECT_NAME})
set(PLUGIN_DIR_NAME ${CMAKE_PROJECT_NAME}.sdPlugin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS false)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE STRING "Minimum MacOS version")
if (MSVC)
add_definitions("/Zc:__cplusplus" -DUNICODE=1)
endif()

include(cmake/StreamDeckSDK.cmake)

set(
    CMAKE_INSTALL_PREFIX
    ${PLUGIN_DIR_NAME}
    CACHE PATH "Default install path"
    FORCE
)

add_subdirectory(src)
add_subdirectory(sdPlugin)

find_program(NPM_BIN NAMES npm)
if(NPM_BIN)
    add_custom_target(
        npm_install
        COMMAND npm i @elgato/cli --no-save
        COMMENT "Installing npm dependencies"
    )
    add_custom_target(
        validate
        DEPENDS npm_install
        COMMAND npx streamdeck validate ${CMAKE_BINARY_DIR}/${PLUGIN_DIR_NAME}
    )
    add_custom_target(
        pack
        DEPENDS npm_install
        COMMAND npx streamdeck pack ${CMAKE_BINARY_DIR}/${PLUGIN_DIR_NAME} -f
    )
else()
    message(WARNING "npm not found, skipping npm targets")
endif()
