

#include "LWindow.h"
#include "LShaderManager.h"
#include "LVertexArray.h"
#include "LVertexBuffer.h"
#include "LIndexBuffer.h"

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

    GLuint _pSimple = engine::LShaderManager::INSTANCE->programs["basic"];
    // cout << "simpleId: " << _pSimple << endl;

    // Quad vertices
    
    // GLfloat _vertices[] = 
    // {
    //     -0.5f, -0.5f,
    //      0.5f, -0.5f,
    //      0.5f,  0.5f,
    //     -0.5f,  0.5f
    // };
    
    // GLfloat _colors[] =
    // {
    //     1.0f, 0.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f,
    //     0.0f, 0.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f
    // };

    // GLuint _indices[] =
    // {
    //     0, 1, 2,
    //     2, 3, 0
    // };
    
    // Quad vertices

    GLfloat* _vertices = new GLfloat[8];
    _vertices[0] = -0.5f; _vertices[1] = -0.5f;
    _vertices[2] =  0.5f; _vertices[3] = -0.5f;
    _vertices[4] =  0.5f; _vertices[5] =  0.5f;
    _vertices[6] = -0.5f; _vertices[7] =  0.5f;

    GLfloat* _colors = new GLfloat[12];
    _colors[0] = 1.0f; _colors[1] = 0.0f;  _colors[2] = 0.0f;
    _colors[3] = 0.0f; _colors[4] = 1.0f;  _colors[5] = 0.0f;
    _colors[6] = 0.0f; _colors[7] = 0.0f;  _colors[8] = 1.0f;
    _colors[9] = 1.0f; _colors[10] = 1.0f; _colors[11] = 1.0f;

    GLuint* _indices = new GLuint[6];
    _indices[0] = 0; _indices[1] = 1; _indices[2] = 2;
    _indices[3] = 2; _indices[4] = 3; _indices[5] = 0;

    engine::LVertexBuffer* _posBuffer = new engine::LVertexBuffer();
    _posBuffer->setData( 8 * sizeof( GLfloat ), 2, _vertices );

    engine::LVertexBuffer* _colorBuffer = new engine::LVertexBuffer();
    _colorBuffer->setData( 12 * sizeof( GLfloat ), 3, _colors );

    engine::LIndexBuffer* _indxBuffer = new engine::LIndexBuffer();
    _indxBuffer->setData( 6 * sizeof( GLuint ), 6, _indices );

    engine::LVertexArray* _vertexArray = new engine::LVertexArray();
    _vertexArray->addBuffer( _posBuffer, 0 );
    _vertexArray->addBuffer( _colorBuffer, 1 );

    delete[] _vertices;
    delete[] _colors;
    delete[] _indices;

    while ( _window.isActive() )
    {
        _window.clear();
        _window.pollEvents();

        // render loop

        glUseProgram( _pSimple );

        _vertexArray->bind();
        _indxBuffer->bind();

        glDrawElements( GL_TRIANGLES, _indxBuffer->getCount(), GL_UNSIGNED_INT, 0 );

        _indxBuffer->unbind();
        _vertexArray->unbind();

        glUseProgram( 0 );

        _window.swapBuffers();
    }

    return 0;
}