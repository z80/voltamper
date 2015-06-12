
find_package( Qt4 )
include( ${QT_USE_FILE} )

include_directories( "./src"
                     ${ROOT}/3dparty/qextserialport/src
                     ${CMAKE_CURRENT_BINARY_DIR} )
if ( WIN32 )
    include_directories( ${BOOST_PATH} )
endif ( WIN32 )

aux_source_directory( "./src" src )

add_library( libio STATIC ${src} )
target_link_libraries( libio serial ${QT_LIBRARIES} )
