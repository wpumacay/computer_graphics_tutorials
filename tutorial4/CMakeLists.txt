


if( WIN44 )

    message( "Building tutorial 4 - windows" )
    add_executable( main_4.exe main_4.cpp )

elseif( UNIX AND NOT APPLE )

    message( "Building tutorial 4 - linux" )
    add_executable( main_4.out 
                    main_4.cpp 
                    LWindow.cpp 
                    LShaderManager.cpp
                    LVertexBuffer.cpp
                    LIndexBuffer.cpp
                    LVertexArray.cpp )

    target_link_libraries( main_4.out
                           ${OPENGL_LIBRARIES} 
                           ${GLFW_LIBRARIES} 
                           GLEW::GLEW 
                           ${X11_LIBRARIES} 
                           ${CMAKE_THREAD_LIBS_INIT}
                           dl )

elseif( APPLE )

    message( "Building tutorial 4 - macOS" )

endif()