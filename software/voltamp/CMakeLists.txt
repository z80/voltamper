
#find_package( Qt4 REQUIRED )
#set( QT_USE_QTGUI true )
#set( QT_USE_QTSVG true )
#include( ${QT_USE_FILE} )

    SET(CMAKE_INCLUDE_CURRENT_DIR ON)
    FIND_PACKAGE(Qt5Widgets)
    FIND_PACKAGE(Qt5Core)
    #FIND_PACKAGE(Qt5Xml)
    #FIND_PACKAGE(Qt5Svg)
    SET(CMAKE_AUTOMOC ON)


include_directories( "./src"
                     ${ROOT}/libio/src
                     ${ROOT}/lib_lua_machine/src
                     ${ROOT}/3dparty/qwt-6.1.2/src
                     ${CMAKE_CURRENT_BINARY_DIR} )
if ( WIN32 )
    include_directories( ${BOOST_PATH} )
endif ( WIN32 )

file( GLOB src     "./src/*.cpp" )
file( GLOB headers "./src/*.h" )
file( GLOB ui      "./src/*.ui" )
message( STATUS "SRC = ${src}" )
message( STATUS "HEADERS = ${headers}" )
message( STATUS "ui = ${ui}" )

#qt5_wrap_cpp( moc_src ${headers} )
#set( src ${src} ${moc_src} )

qt5_wrap_ui( moc_src ${ui} )
set( src ${src} ${moc_src} )

add_executable( voltamp ${src} )
qt5_use_modules( voltamp Widgets Core )
target_link_libraries( voltamp libio qwt-6.1.2 ${QT_LIBRARIES} )
install( TARGETS voltamp DESTINATION ./ )
