if(APPLE)
    set(DEFAULT_CODE_PATH_MAC streamdeck-ram)
elseif(WIN32)
    set(DEFAULT_CODE_PATH_WIN streamdeck-ram.exe)
endif()

set(CODE_PATH_MAC ${DEFAULT_CODE_PATH_MAC} CACHE STRING "Mac binary code path")
set(CODE_PATH_WIN ${DEFAULT_CODE_PATH_WIN} CACHE STRING "Windows binary code path")

if(APPLE)
    set(CODE_PATHS "\"CodePath\": \"${CODE_PATH_MAC}\"")
    if(NOT CODE_PATH_WIN STREQUAL "")
        list(APPEND CODE_PATH "\"CodePathWin\": \"${CODE_PATH_WIN}\"")
    endif()
elseif(WIN32)
    set(CODE_PATHS "\"CodePath\": \"${CODE_PATH_WIN}\"")
    if(NOT CODE_PATH_MAC STREQUAL "")
        list(APPEND CODE_PATHS "\"CodePathMac\": \"${CODE_PATH_MAC}\"")
    endif()
endif()
list(JOIN CODE_PATHS ", " CODE_PATHS)

configure_file(
    manifest.in
    manifest.json
    NEWLINE_STYLE UNIX
)

file(GLOB STATIC_FILES *.png *.svg *.json)

install(
    FILES
    ${STATIC_FILES}
    ${CMAKE_CURRENT_BINARY_DIR}/manifest.json
    DESTINATION .
)
