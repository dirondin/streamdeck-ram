function(get_streamdeck_code_paths_json OUTPUT)
    cmake_parse_arguments(PARSE_ARGV 0 arg "" "MAC;WIN" "")

    set(STREAMDECK_CODE_PATH_MAC "" CACHE PATH "Override path to macOS plugin binary")
    set(STREAMDECK_CODE_PATH_WIN "" CACHE PATH "Override path to Windows plugin binary")

    set(CODE_PATH_MAC_NAME "")
    if(NOT STREAMDECK_CODE_PATH_MAC STREQUAL "")
        get_filename_component(CODE_PATH_MAC_NAME ${STREAMDECK_CODE_PATH_MAC} NAME)
    endif()
    set(CODE_PATH_WIN_NAME "")
    if(NOT STREAMDECK_CODE_PATH_WIN STREQUAL "")
        get_filename_component(CODE_PATH_WIN_NAME ${STREAMDECK_CODE_PATH_WIN} NAME)
    endif()

    if(APPLE)
        if(CODE_PATH_MAC_NAME STREQUAL "")
            set(CODE_PATH_MAC_NAME ${arg_MAC})
        endif()

        set(CODE_PATHS "\"CodePath\": \"${CODE_PATH_MAC_NAME}\"")
        if(NOT CODE_PATH_WIN_NAME STREQUAL "")
            list(APPEND CODE_PATH "\"CodePathWin\": \"${CODE_PATH_WIN_NAME}\"")
        endif()
    elseif(WIN32)
        if(CODE_PATH_WIN_NAME STREQUAL "")
            set(CODE_PATH_WIN_NAME ${arg_WIN})
        endif()

        set(CODE_PATHS "\"CodePath\": \"${CODE_PATH_WIN_NAME}\"")
        if(NOT CODE_PATH_MAC_NAME STREQUAL "")
            list(APPEND CODE_PATHS "\"CodePathMac\": \"${CODE_PATH_MAC_NAME}\"")
        endif()
    endif()
    list(JOIN CODE_PATHS ", " CODE_PATHS)

    set(${OUTPUT} ${CODE_PATHS} PARENT_SCOPE)
endfunction()


function(add_streamdeck_distribute_targets PLUGIN_UUID PLUGIN_PATH)
    find_program(NPM_BIN NAMES npm)
    if(NPM_BIN)
        add_custom_target(
            npm-install
            COMMAND npm i @elgato/cli --no-save
            COMMENT "Installing npm dependencies"
        )
        add_custom_target(
            plugin-validate
            DEPENDS npm-install
            COMMAND npx streamdeck validate ${PLUGIN_PATH}
        )
        add_custom_target(
            plugin-pack
            DEPENDS npm-install
            COMMAND npx streamdeck pack ${PLUGIN_PATH} -f
        )
        add_custom_target(
            plugin-link
            DEPENDS npm-install
            COMMAND npx streamdeck link ${PLUGIN_PATH}
        )
        add_custom_target(
            plugin-restart
            DEPENDS npm-install
            COMMAND npx streamdeck r ${PLUGIN_UUID}
        )
        add_custom_target(
            plugin-stop
            DEPENDS npm-install
            COMMAND npx streamdeck s ${PLUGIN_UUID}
        )
    else()
        message(WARNING "npm not found, skipping npm targets")
    endif()
endfunction()


function(add_streamdeck_deploy_targets PLUGIN_DIR_NAME)
    set(DEPLOY_PATH ${CMAKE_BINARY_DIR}/${PLUGIN_DIR_NAME})
    add_custom_target(pre-deploy
        COMMAND ${CMAKE_COMMAND} -E make_directory ${DEPLOY_PATH}
    )
    add_custom_target(deploy ALL DEPENDS pre-deploy)
    set_target_properties(deploy PROPERTIES DEPLOY_PATH ${CMAKE_BINARY_DIR}/${PLUGIN_DIR_NAME})
endfunction()


function(add_streamdeck_deploy_target TARGET)
    set(DEPLOY_TARGET_NAME deploy-${TARGET})
    get_target_property(DEPLOY_PATH deploy DEPLOY_PATH)
    add_custom_target(
        ${DEPLOY_TARGET_NAME}
        DEPENDS ${DEPLOY_TARGET_NAME} pre-deploy
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET}> ${DEPLOY_PATH}
    )
    add_dependencies(deploy ${DEPLOY_TARGET_NAME})
endfunction()


function(add_streamdeck_deploy_static NAME STATIC_FILES)
    set(STATIC_FILES ${STATIC_FILES} ${ARGN})
    set(DEPLOY_TARGET_NAME deploy-${NAME})
    get_target_property(DEPLOY_PATH deploy DEPLOY_PATH)
    add_custom_target(
        ${DEPLOY_TARGET_NAME}
        DEPENDS pre-deploy
        COMMAND ${CMAKE_COMMAND} -E copy ${STATIC_FILES} ${DEPLOY_PATH}
    )
    add_dependencies(deploy ${DEPLOY_TARGET_NAME})
endfunction()


function(set_default_install_prefix_to_streamdeck_plugin_dir PLUGIN_DIR)
    set(SET_INSTALL_PREFIX_TO_STREAMDECK_PLUGIN_DIR OFF CACHE BOOL "Use StreamDeck plugin directory as install prefix")
    if(SET_INSTALL_PREFIX_TO_STREAMDECK_PLUGIN_DIR)
        set(
            CMAKE_INSTALL_PREFIX
            ${STREAMDECK_PLUGIN_DIR}/${PLUGIN_DIR}
            CACHE PATH "See cmake documentation"
            FORCE
        )
    endif()
endfunction()

