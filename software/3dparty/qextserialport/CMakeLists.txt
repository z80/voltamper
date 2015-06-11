# Поиск и присоединение заголовков Qt.
find_package( Qt4 )
include( ${QT_USE_FILE} )

# Собственные поддиректории заголовочных файлов.
include_directories( "src"
                     "${CMAKE_CURRENT_BINARY_DIR}/src" )

# Includes.
list( APPEND headers "./src/qextserialport.h" )
list( APPEND headers "./src/qextserialenumerator.h" )
list( APPEND headers "./src/qextserialport_global.h" )

list( APPEND headers "./src/qextserialenumerator_p.h" )
list( APPEND headers "./src/qextserialport_p.h" )

# Файлы исходного кода.
list( APPEND com_src "./src/qextserialenumerator.cpp" )
list( APPEND com_src "./src/qextserialport.cpp" )
if( WIN32 )
    list( APPEND com_src "./src/qextserialenumerator_win.cpp" )
    list( APPEND com_src "./src/qextserialport_win.cpp" )
    set( defs _TTY_WIN_ Q_OS_WIN )
else( WIN32 )
    list( APPEND com_src "./src/qextserialenumerator_linux.cpp" )
    list( APPEND com_src "./src/qextserialport_unix.cpp" )
    set( defs _TTY_POSIX_ __linux__ Q_OS_UNIX )
endif( WIN32 )
message( STATUS "SERIAL DEFS: ${defs}" )

qt4_wrap_cpp( moc_src ${headers} )
set( com_src ${com_src} ${moc_src} )

# Статическая, поскольку хотелось бы только в одном месте использовать.
add_library( serial STATIC ${com_src} )
target_link_libraries( serial ${QT_LIBRARIES} )
# Символы для импорта динамических библиотек.
set_property( TARGET serial PROPERTY DEFINE_SYMBOL ${defs} )

set_property( TARGET serial PROPERTY COMPILE_DEFINITIONS ${defs} )

message( STATUS "configuring serial" )
