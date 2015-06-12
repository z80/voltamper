
find_package( Qt4 )
include( ${QT_USE_FILE} )

include_directories( "./src"
                     ${ROOT}/libio/src
                     ${CMAKE_CURRENT_BINARY_DIR} )

aux_source_directory( "./src" src )

add_executable( test ${src} )
target_link_libraries( test libio ${QT_LIBRARIES} )
install( TARGETS test DESTINATION ./ )



