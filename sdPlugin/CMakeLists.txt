set(CODE_PATH_MAC "" CACHE PATH "Override path to macOS plugin binary")
set(CODE_PATH_WIN "" CACHE PATH "Override path to Windows plugin binary")

set(CODE_PATH_MAC_NAME "")
if(NOT CODE_PATH_MAC STREQUAL "")
    get_filename_component(CODE_PATH_MAC_NAME ${CODE_PATH_MAC} NAME)
    install(
        FILES
        ${CODE_PATH_MAC}
        DESTINATION .
    )
endif()
set(CODE_PATH_WIN_NAME "")
if(NOT CODE_PATH_WIN STREQUAL "")
    get_filename_component(CODE_PATH_WIN_NAME ${CODE_PATH_WIN} NAME)
    install(
        FILES
        ${CODE_PATH_WIN}
        DESTINATION .
    )
endif()
if(APPLE)
    if(CODE_PATH_MAC_NAME STREQUAL "")
        set(CODE_PATH_MAC_NAME streamdeck-ram)
    endif()

    set(CODE_PATHS "\"CodePath\": \"${CODE_PATH_MAC_NAME}\"")
    if(NOT CODE_PATH_WIN_NAME STREQUAL "")
        list(APPEND CODE_PATH "\"CodePathWin\": \"${CODE_PATH_WIN_NAME}\"")
    endif()
elseif(WIN32)
    if(CODE_PATH_WIN_NAME STREQUAL "")
        set(CODE_PATH_WIN_NAME streamdeck-ram.exe)
    endif()

    set(CODE_PATHS "\"CodePath\": \"${CODE_PATH_WIN_NAME}\"")
    if(NOT CODE_PATH_MAC_NAME STREQUAL "")
        list(APPEND CODE_PATHS "\"CodePathMac\": \"${CODE_PATH_MAC_NAME}\"")
    endif()
endif()
list(JOIN CODE_PATHS ", " CODE_PATHS)

file(GLOB STATIC_FILES *.png *.svg *.json)

file(GLOB CONFIG_FILES *.in)
foreach(CONFIG_FILE ${CONFIG_FILES})
    get_filename_component(CONFIG_FILE_NAME ${CONFIG_FILE} NAME_WLE)
    configure_file(
        ${CONFIG_FILE}
        ${CONFIG_FILE_NAME}
        NEWLINE_STYLE UNIX
    )
    list(APPEND STATIC_FILES ${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE_NAME})
endforeach()

install(
    FILES
    ${STATIC_FILES}
    DESTINATION .
)
