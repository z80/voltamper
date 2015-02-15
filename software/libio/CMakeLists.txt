
include_directories( "./src"
                     ${CMAKE_CURRENT_BINARY_DIR} )

aux_source_directory( "./src" src )

add_library( libio STATIC ${src} )

target_link_libraries( libio ${libusb} )
