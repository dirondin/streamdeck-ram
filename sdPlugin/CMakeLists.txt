get_streamdeck_code_paths_json(CODE_PATHS)

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

list(APPEND STATIC_FILES ${STREAMDECK_CODE_PATH_MAC} ${STREAMDECK_CODE_PATH_WIN})

add_streamdeck_deploy_static(sdPlugin ${STATIC_FILES})
