

#include "LWindow.h"
#include "LShaderManager.h"
#include "LVertexArray.h"
#include "LVertexBuffer.h"
#include "LIndexBuffer.h"

#include "LMeshBuilder.h"
#include "LMesh.h"

#include <iostream>

using namespace std;

bool g_isWireframe = false;

void onKeyCallback( int key, int action )
{
    if ( action == GLFW_PRESS )
    {
        if ( key == GLFW_KEY_W )
        {
            g_isWireframe = !g_isWireframe;
            if ( g_isWireframe )
            {
                cout << "changed to wireframe" << endl;
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            }
            else
            {
                cout << "changed to fill" << endl;
                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            }
        }
    }
}

int main()
{
    engine::LWindow _window;

    _window.registerKeyCallback( onKeyCallback );

    // Initialize shader manager
    engine::LShaderManager::create();

    GLuint _pSimple3d = engine::LShaderManager::INSTANCE->programs["basic3d"];

    engine::LMesh* _cube = engine::LMeshBuilder::createBox( 0.5, 0.5, 0.5 );

    engine::LMesh* _plane = engine::LMeshBuilder::createPlane( 10.0f, 10.0f );

    glm::vec3 _cameraPos( 7.0f, 3.0f, -10.0f );
    glm::vec3 _cameraDir( -7.0f, -3.0f, 10.0f );
    glm::vec3 _cameraTarget = _cameraPos + _cameraDir;
    glm::vec3 _worldUp( 0.0f, 1.0f, 0.0f );

    glm::mat4 _viewMatrix = glm::lookAt( _cameraPos,
                                         _cameraTarget,
                                         _worldUp );

    glm::mat4 _projMatrix = glm::perspective( glm::radians( 45.0f ),
                                              (float) _window.width() / _window.height(),
                                              0.1f, 100.0f );

    _cube->pos = engine::LVec3( 3.0f, 1.0f, 5.0f );

    while ( _window.isActive() )
    {
        _window.clear();
        _window.pollEvents();

        // render loop

        glUseProgram( _pSimple3d );

        // Drawing cube
        GLuint u_tModel = glGetUniformLocation( _pSimple3d, "u_tModel" );
        GLuint u_tView = glGetUniformLocation( _pSimple3d, "u_tView" );
        GLuint u_tProj = glGetUniformLocation( _pSimple3d, "u_tProj" );

        glUniformMatrix4fv( u_tModel, 1, GL_FALSE, glm::value_ptr( _cube->getModelMatrix() ) );
        glUniformMatrix4fv( u_tView, 1, GL_FALSE, glm::value_ptr( _viewMatrix ) );
        glUniformMatrix4fv( u_tProj, 1, GL_FALSE, glm::value_ptr( _projMatrix ) );

        _cube->getVertexArray()->bind();
        _cube->getIndexBuffer()->bind();

        glDrawElements( GL_TRIANGLES, 
                        _cube->getIndexBuffer()->getCount(), 
                        GL_UNSIGNED_INT, 0 );

        _cube->getVertexArray()->unbind();
        _cube->getIndexBuffer()->unbind();

        // Drawing plane
        glUniformMatrix4fv( u_tModel, 1, GL_FALSE, glm::value_ptr( _plane->getModelMatrix() ) );

        _plane->getVertexArray()->bind();
        _plane->getIndexBuffer()->bind();

        glDrawElements( GL_TRIANGLES, 
                        _plane->getIndexBuffer()->getCount(), 
                        GL_UNSIGNED_INT, 0 );

        _plane->getVertexArray()->unbind();
        _plane->getIndexBuffer()->unbind();

        glUseProgram( 0 );

        _window.swapBuffers();
    }

    return 0;
}