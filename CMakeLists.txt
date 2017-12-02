cmake_minimum_required( VERSION 3.5.0 )
project( tutorials C CXX )

set( CMAKE_BUILD_TYPE Debug )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS_DEBUG "-g" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3" )



if( WIN32 )

    message( "GENERATING SOLUTIONS FOR WINDOWS" )

    include_directories( lib/glfw/include/
                         lib/glm/
                         lib/glew/include )

    link_directories( lib/glfw/lib
                      lib/glew/lib )

elseif( UNIX AND NOT APPLE )

    message( "GENERATING MAKEFILES/PROJECTS FOR LINUX" )

    find_package( OpenGL REQUIRED )
    find_package( GLEW REQUIRED )
    find_package( X11 REQUIRED )
    find_package( Threads REQUIRED )
    find_package( PkgConfig REQUIRED )
    pkg_search_module( GLFW REQUIRED glfw3 )

    include_directories( /usr/local/include )
    link_directories( /usr/local/lib )

elseif( APPLE )

    message( "GENERATING MAKEFILES/PROJECTS FOR MACOS" )

endif()


add_subdirectory( tutorial1 )
add_subdirectory( tutorial2 )
add_subdirectory( tutorial3 )
add_subdirectory( tutorial4 )




