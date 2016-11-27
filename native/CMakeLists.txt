aux_source_directory(. SRC_LIST)

set(X11_HEADERS_PATH /usr/include)
set(X11_LIBRARY_PATH /usr/lib)

set(SDL_HEADERS_PATH /usr/include/SDL2)
set(SDL_LIBRARY_PATH /usr/lib64/)

set(PNG_HEADERS_PATH /usr/include/libpng16)

set(FREETYPE2_LIBRARY_PATH /home/nikola/software/freetype-2.4.0/lib)

include_directories(
    X11_HEADERS_PATH
    SDL_HEADERS_PATH
    PNG_HEADERS_PATH  )

link_directories(
    X11_LIBRARY_PATH
    SDL_LIBRARY_PATH
    FREETYPE2_LIBRARY_PATH )

add_definitions(-DUSE_X)

add_library(native ${SRC_LIST})
target_link_libraries(native X11 SDL2 SDL2_image freetype rt)
