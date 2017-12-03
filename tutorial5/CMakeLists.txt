


if( WIN44 )

    message( "Building tutorial 5 - windows" )
    add_executable( main_5.exe main_5.cpp )

elseif( UNIX AND NOT APPLE )

    message( "Building tutorial 5 - linux" )
    add_executable( main_5.out 
                    main_5.cpp 
                    LWindow.cpp 
                    LShaderManager.cpp
                    LVertexBuffer.cpp
                    LIndexBuffer.cpp
                    LVertexArray.cpp
                    LMesh.cpp
                    LMeshBuilder.cpp )

    target_link_libraries( main_5.out
                           ${OPENGL_LIBRARIES} 
                           ${GLFW_LIBRARIES} 
                           GLEW::GLEW 
                           ${X11_LIBRARIES} 
                           ${CMAKE_THREAD_LIBS_INIT}
                           dl )

elseif( APPLE )

    message( "Building tutorial 5 - macOS" )

endif()