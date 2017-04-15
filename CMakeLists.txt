project(UI)
cmake_minimum_required(VERSION 2.8)

include_directories("${PROJECT_SOURCE_DIR}/ui")
include_directories("${PROJECT_SOURCE_DIR}/gl")
include_directories("${PROJECT_SOURCE_DIR}/native")

add_subdirectory(gl)
add_subdirectory(native)
add_subdirectory(ui)

add_definitions(-std=c++03)

add_executable(${PROJECT_NAME} main.cpp channel_view.cpp)

target_link_libraries(${PROJECT_NAME}
    gl
    ui
    native
    EGL
    GLESv2
    X11
    SDL2
    SDL2_image
    freetype
    rt )
