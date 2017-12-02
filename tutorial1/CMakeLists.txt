


if( WIN32 )

    message( "Building tutorial 1 - linux" )
    add_executable( main_1.exe main_1.cpp glfw3 glew )

elseif( UNIX AND NOT APPLE )

    message( "Building tutorial 1 - linux" )
    add_executable( main_1.out main_1.cpp )
    target_link_libraries( main_1.out
                           ${OPENGL_LIBRARIES} 
                           ${GLFW_LIBRARIES} 
                           GLEW::GLEW 
                           ${X11_LIBRARIES} 
                           ${CMAKE_THREAD_LIBS_INIT}
                           dl )

elseif( APPLE )

    message( "GENERATING MAKEFILES/PROJECTS FOR MACOS" )

endif()