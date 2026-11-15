cmake_minimum_required(VERSION 3.11)

project(psp-lifecounter)

add_executable(${PROJECT_NAME}
  src/main.c
  src/common/callback.c
  src/common/player.c
  src/common/ui.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/common
)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
find_package(SDL3_ttf REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pspdebug
    pspdisplay
    pspge
    pspctrl
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
)

# Create an EBOOT.PBP file
create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH ../res/ICON0.png
    BACKGROUND_PATH NULL
    PREVIEW_PATH NULL
    TITLE ${PROJECT_NAME}
    VERSION 01.00
)
