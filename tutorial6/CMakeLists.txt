


if( WIN44 )

    message( "Building tutorial 6 - windows" )
    add_executable( main_6.exe main_6.cpp )

elseif( UNIX AND NOT APPLE )

    message( "Building tutorial 6 - linux" )
    add_executable( main_6.out 
                    main_6.cpp 
                    LComponent.cpp
                    LEntity.cpp
                    LFixedCamera3d.cpp
                    LICamera.cpp
                    LILight.cpp
                    LIndexBuffer.cpp
                    LLightDirectional.cpp
                    LMaterial.cpp
                    LMeshBuilder.cpp
                    LMeshComponent.cpp
                    LMesh.cpp
                    LScene.cpp
                    LSceneRenderer.cpp
                    LShaderManager.cpp
                    LVertexArray.cpp
                    LVertexBuffer.cpp
                    LWindow.cpp )

    target_link_libraries( main_6.out
                           ${OPENGL_LIBRARIES} 
                           ${GLFW_LIBRARIES} 
                           GLEW::GLEW 
                           ${X11_LIBRARIES} 
                           ${CMAKE_THREAD_LIBS_INIT}
                           dl )

elseif( APPLE )

    message( "Building tutorial 6 - macOS" )

endif()