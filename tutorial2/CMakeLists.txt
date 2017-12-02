


if( WIN32 )

    message( "Building tutorial 2 - windows" )
    add_executable( main_2.exe main_2.cpp )

elseif( UNIX AND NOT APPLE )

    message( "Building tutorial 2 - linux" )
    add_executable( main_2.out main_2.cpp LWindow.cpp )
    target_link_libraries( main_2.out
                           ${OPENGL_LIBRARIES} 
                           ${GLFW_LIBRARIES} 
                           GLEW::GLEW 
                           ${X11_LIBRARIES} 
                           ${CMAKE_THREAD_LIBS_INIT}
                           dl )

elseif( APPLE )

    message( "Building tutorial 2 - macOS" )

endif()