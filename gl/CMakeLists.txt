aux_source_directory(. SRC_LIST)

set(EGL_LIBRARY_PATH /usr/lib)
set(EGL_HEADERS_PATH /usr/include)
set(GLES2_LIBRARY_PATH /usr/lib)
set(GLES2_HEADERS_PATH /usr/include)

include_directories(
    EGL_HEADERS_PATH
    GLES2_HEADERS_PATH
    /home/nikola/software/freetype-2.4.0/include)

link_directories(
    EGL_LIBRARY_PATH
    GLES2_LIBRARY_PATH  )

add_library(gl ${SRC_LIST})
#target_link_libraries( gl  )

