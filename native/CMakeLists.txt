aux_source_directory(. SRC_LIST)

set(X11_HEADERS_PATH /usr/include)
set(X11_LIBRARY_PATH /usr/lib)

include_directories( X11_HEADERS_PATH )
link_directories( X11_LIBRARY_PATH )

add_definitions(-DUSE_X)

add_library(native ${SRC_LIST})
target_link_libraries(native X11)
