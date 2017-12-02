


if( WIN33 )

    message( "Building tutorial 3 - windows" )
    add_executable( main_3.exe main_3.cpp )

elseif( UNIX AND NOT APPLE )

    message( "Building tutorial 3 - linux" )
    add_executable( main_3.out main_3.cpp LWindow.cpp )
    target_link_libraries( main_3.out
                           ${OPENGL_LIBRARIES} 
                           ${GLFW_LIBRARIES} 
                           GLEW::GLEW 
                           ${X11_LIBRARIES} 
                           ${CMAKE_THREAD_LIBS_INIT}
                           dl )

elseif( APPLE )

    message( "Building tutorial 3 - macOS" )

endif()