aux_source_directory(. SRC_LIST)

set(X11_HEADERS_PATH /usr/include)
set(X11_LIBRARY_PATH /usr/lib)
set(PNG_HEADERS_PATH /usr/include/libpng16)
set(FREETYPE2_INCLUDE_PATH /usr/include/freetype2)
set(FREETYPE2_LIBRARY_PATH /usr/lib)

include_directories( X11_HEADERS_PATH FREETYPE2_INCLUDE_PATH PNG_HEADERS_PATH )
link_directories( X11_LIBRARY_PATH FREETYPE2_LIBRARY_PATH )

add_definitions(-DUSE_X)

add_library(native ${SRC_LIST})
target_link_libraries(native X11 freetype)
