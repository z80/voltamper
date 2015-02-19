
find_package( Qt4 REQUIRED )
set( QT_USE_QTGUI true )
set( QT_USE_QTSVG true )
include( ${QT_USE_FILE} )

include_directories( "./src"
                     ${ROOT}/libio/src
                     ${CMAKE_CURRENT_BINARY_DIR} )

file( GLOB src     "./src/*.cpp" )
file( GLOB headers "./src/*.h" )
file( GLOB ui      "./src/*.ui" )
message( STATUS "SRC = ${src}" )
message( STATUS "HEADERS = ${headers}" )
message( STATUS "ui = ${ui}" )

qt4_wrap_cpp( moc_src ${headers} )
set( src ${src} ${moc_src} )

qt4_wrap_ui( moc_src ${ui} )
set( src ${src} ${moc_src} )

add_executable( voltamp ${src} )
target_link_libraries( voltamp libio ${QT_LIBRARIES} )









