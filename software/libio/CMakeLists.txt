
find_package( Qt4 )
include( ${QT_USE_FILE} )

include_directories( "./src"
                     ${ROOT}/3dparty/qextserialport/src
                     ${CMAKE_CURRENT_BINARY_DIR} )

aux_source_directory( "./src" src )

add_library( libio STATIC ${src} )
target_link_libraries( libio serial ${QT_LIBRARIES} )
