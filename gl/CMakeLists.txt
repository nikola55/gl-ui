aux_source_directory(. SRC_LIST)

set(EGL_LIBRARY_PATH /usr/lib)
set(EGL_HEADERS_PATH /usr/include)
set(GLES2_LIBRARY_PATH /usr/lib)
set(GLES2_HEADERS_PATH /usr/include)
set(SDL_HEADERS_PATH /usr/include/SDL2)
set(SDL_LIBRARY_PATH /usr/lib64/)

include_directories( EGL_HEADERS_PATH GLES2_HEADERS_PATH SDL_HEADERS_PATH )
link_directories( EGL_LIBRARY_PATH GLES2_LIBRARY_PATH SDL_LIBRARY_PATH )

add_library(gl ${SRC_LIST})
target_link_libraries(gl SDL2 SDL2_image EGL GLESv2 native ui)

