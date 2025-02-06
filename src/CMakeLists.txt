set(
    SOURCES
    main.cpp
    Plugin.cpp
    ThreadTimer.cpp
    UsageAction.cpp
)

if(APPLE)
    list(APPEND SOURCES mac/MacPlatformUtils.cpp)
elseif(WIN32)
    list(APPEND SOURCES win/WinPlatformUtils.cpp)
endif()

add_executable(streamdeck-ram ${SOURCES})
target_include_directories(streamdeck-ram PRIVATE .)
target_link_libraries(streamdeck-ram StreamDeckSDK)

add_streamdeck_deploy_target(streamdeck-ram)

