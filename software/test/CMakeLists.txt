
#find_package( Qt4 )
#include( ${QT_USE_FILE} )

    SET(CMAKE_INCLUDE_CURRENT_DIR ON)
    FIND_PACKAGE(Qt5Widgets)
    FIND_PACKAGE(Qt5Core)
    #FIND_PACKAGE(Qt5Xml)
    #FIND_PACKAGE(Qt5Svg)
    SET(CMAKE_AUTOMOC ON)

include_directories( "./src"
                     ${ROOT}/libio/src
                     ${ROOT}/3dparty/qextserialport/src
                     ${CMAKE_CURRENT_BINARY_DIR} )

aux_source_directory( "./src" src )

add_executable( test ${src} )
qt5_use_modules( test Widgets Core )
target_link_libraries( test libio ${QT_LIBRARIES} )
install( TARGETS test DESTINATION ./ )



