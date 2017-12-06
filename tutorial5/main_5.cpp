

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

    glEnable( GL_DEPTH_TEST );

    // Initialize shader manager
    engine::LShaderManager::create();

    GLuint _pSimple3d = engine::LShaderManager::INSTANCE->programs["basic3d"];

    //engine::LMesh* _cube = engine::LMeshBuilder::createBox( 0.5, 0.5, 0.5 );
    engine::LMesh* _sphere = engine::LMeshBuilder::createFromFile( "../res/models/model_sphere_1024.obj" );

    engine::LMesh* _plane = engine::LMeshBuilder::createPlane( 10.0f, 12.0f );
    _plane->pos = engine::LVec3( 0.0f, 0.0f, 2.0f );

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

    _sphere->pos = engine::LVec3( 3.0f, 1.0f, 5.0f );

    while ( _window.isActive() )
    {
        _window.clear();
        _window.pollEvents();

        // render loop

        glUseProgram( _pSimple3d );

        
        GLuint u_tModel = glGetUniformLocation( _pSimple3d, "u_tModel" );
        GLuint u_tView = glGetUniformLocation( _pSimple3d, "u_tView" );
        GLuint u_tProj = glGetUniformLocation( _pSimple3d, "u_tProj" );
        GLuint u_color = glGetUniformLocation( _pSimple3d, "u_color" );

        glUniformMatrix4fv( u_tView, 1, GL_FALSE, glm::value_ptr( _viewMatrix ) );
        glUniformMatrix4fv( u_tProj, 1, GL_FALSE, glm::value_ptr( _projMatrix ) );

        // Drawing sphere
        glUniformMatrix4fv( u_tModel, 1, GL_FALSE, glm::value_ptr( _sphere->getModelMatrix() ) );
        glUniform3f( u_color, 1.0f, 0.84f, 0.0f );

        _sphere->getVertexArray()->bind();
        _sphere->getIndexBuffer()->bind();

        glDrawElements( GL_TRIANGLES, 
                        _sphere->getIndexBuffer()->getCount(), 
                        GL_UNSIGNED_INT, 0 );

        _sphere->getVertexArray()->unbind();
        _sphere->getIndexBuffer()->unbind();

        // Drawing plane
        glUniformMatrix4fv( u_tModel, 1, GL_FALSE, glm::value_ptr( _plane->getModelMatrix() ) );
        glUniform3f( u_color, 0.0f, 1.0f, 0.0f );

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
