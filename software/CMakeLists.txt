
project( voltamper )
cmake_minimum_required(VERSION 2.8)

set( CMAKE_INSTALL_PREFIX ./app )
set( ROOT ${CMAKE_CURRENT_SOURCE_DIR} )
set( _3DPARTY ${CMAKE_CURRENT_SOURCE_DIR}/3dparty )

if ( WIN32 )
    include( "./settings.win32.cmake" )
elseif ( UNIX )
    include( "./settings.unix.cmake" )
endif ( WIN32 )


find_library( icee   NAMES icee_static.lib
                           libIceE.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
find_library( iceec  NAMES iceec_static.lib
                           libIceEC.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
find_library( iceed  NAMES icee_staticd.lib
                           libIceE.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
find_library( iceecd NAMES iceec_staticd.lib
                           libIceEC.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
message( STATUS $ENV{PATH} )
if ( WIN32 )
    find_library( rpcrt4   NAMES rpcrt4.lib   PATHS  $ENV{PATH} "./3dparty" )
    find_library( ws2_32   NAMES ws2_32.lib   PATHS  $ENV{PATH} "./3dparty" )
elseif ( UNIX )
    #find_library( pthread NAMES libpthread.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
    #find_library( rt      NAMES librt.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
endif ( WIN32 )

add_subdirectory( "./3dparty" )
add_subdirectory( "./libio" )
add_subdirectory( "./test" )
add_subdirectory( "./voltamp" )
