cmake_minimum_required(VERSION 3.6.0)
project(bangcardgame VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(bangclient_srcs
    src/image_serial.cpp
    src/intl.cpp
    src/entrypoint.cpp
    src/manager.cpp
    src/chat_ui.cpp
    src/media_pak.cpp
    src/os_api.cpp
    src/gamescene/animations.cpp
    src/gamescene/card.cpp
    src/gamescene/player.cpp
    src/gamescene/game.cpp
    src/gamescene/game_ui.cpp
    src/gamescene/game_message_box.cpp
    src/gamescene/target_finder.cpp
    src/scenes/connect.cpp
    src/scenes/loading.cpp
    src/scenes/lobby_list.cpp
    src/scenes/lobby.cpp
    src/widgets/button.cpp
    src/widgets/checkbox.cpp
    src/widgets/textbox.cpp
    src/widgets/text_list.cpp
    src/widgets/profile_pic.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2 IMPORTED_TARGET)
pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf IMPORTED_TARGET)
pkg_check_modules(SDL2_image REQUIRED SDL2_image IMPORTED_TARGET)
pkg_check_modules(SDL2_gfx REQUIRED SDL2_gfx IMPORTED_TARGET)

find_package(fmt REQUIRED)
if (TARGET fmt::fmt-header-only)
    link_libraries(fmt::fmt-header-only)
else()
    link_libraries(fmt::fmt)
endif()

add_subdirectory(resources)
add_subdirectory(external/banggame)
add_subdirectory(external/tiny-process-library)

set_target_properties(bangserver PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set_target_properties(tiny-process-library PROPERTIES
    POSITION_INDEPENDENT_CODE ON)

add_library(bangclient SHARED ${bangclient_srcs})
target_include_directories(bangclient PRIVATE src)

target_compile_definitions(bangclient PRIVATE SDL_MAIN_HANDLED)

include(GenerateExportHeader)
generate_export_header(bangclient
    EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/exports/bangclient_export.h"
)

target_include_directories(bangclient PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/exports")

target_link_libraries(bangclient PUBLIC PkgConfig::SDL2 PkgConfig::SDL2_ttf PkgConfig::SDL2_image PkgConfig::SDL2_gfx)
target_link_libraries(bangclient PUBLIC bangcommon game_options tiny-process-library)

add_dependencies(bangclient cards_pak media_pak)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    if (WIN32)
        add_executable(banglauncher WIN32 src/main.c resources/bang.rc)
        if (MINGW)
            target_link_options(banglauncher PRIVATE -mconsole)
        endif()
    else()
        add_executable(banglauncher src/main.c)
    endif()

    target_link_libraries(banglauncher bangclient)
endif()