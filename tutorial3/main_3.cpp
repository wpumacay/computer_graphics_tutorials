

#include "LWindow.h"

#include <iostream>

using namespace std;

const char* g_vShader = 
"   #version 330 core\n"
"    \n"
"    layout ( location = 0 ) in vec2 pos;\n"
"    layout ( location = 1 ) in vec3 color;\n"
"    \n"
"    out vec3 fColor;\n"
"    void main() \n"
"    {\n "
"        gl_Position = vec4( pos, 0.0f, 1.0f );\n"
"        fColor = color;\n"
"    }\n\0";


const char* g_fShader =
"   #version 330 core\n"
"   \n"
"   in vec3 fColor;\n"
"   out vec4 FragColor;\n"
"   void main() \n"
"   {\n"
"        FragColor = vec4( fColor, 1.0f );\n"
"   }\n\0";

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

    GLint _success;
    GLchar _infoLog[1024];

    // Load vertex shader *****************
    GLuint _vertexShaderId = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( _vertexShaderId, 1, &g_vShader, NULL );
    glCompileShader( _vertexShaderId );
    glGetShaderiv( _vertexShaderId, GL_COMPILE_STATUS,
                   &_success );

    if ( !_success )
    {
        glGetShaderInfoLog( _vertexShaderId, 1024, 
                            NULL, _infoLog );
        cout << "Failed compiling vertex shader" << endl;
        cout << "Error: " << _infoLog << endl;

        return -1;
    }

    // Load fragment shader ***************
    GLuint _fragmentShaderId = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( _fragmentShaderId, 1, &g_fShader, NULL );
    glCompileShader( _fragmentShaderId );
    glGetShaderiv( _fragmentShaderId, GL_COMPILE_STATUS,
                   &_success );

    if ( !_success )
    {
        glGetShaderInfoLog( _fragmentShaderId, 1024, 
                            NULL, _infoLog );
        cout << "Failed compiling fragment shader" << endl;
        cout << "Error: " << _infoLog << endl;

        return -1;
    }

    // Link into a program **********************
    GLuint _programId = glCreateProgram();
    glAttachShader( _programId, _vertexShaderId );
    glAttachShader( _programId, _fragmentShaderId );
    glLinkProgram( _programId );

    glDetachShader( _programId, _vertexShaderId );
    glDetachShader( _programId, _fragmentShaderId );
    glDeleteShader( _vertexShaderId );
    glDeleteShader( _fragmentShaderId );

    glGetProgramiv( _programId, GL_LINK_STATUS, &_success );
    if ( !_success )
    {
        glGetProgramInfoLog( _programId, 1024, NULL, _infoLog );
        cout << "LINKING ERROR: " << _infoLog << endl;

        return -1;
    }

    cout << "programid: " << _programId << endl;

    // Define some simple geometry

    // Triangle vertices
    //GLfloat _vertices[] = 
    //{
    //    -0.5f, -0.5f,
    //     0.5f, -0.5f,
    //     0.0f,  0.5f
    //};

    // Quad vertices
    GLfloat _vertices[] = 
    {
        // positions -      Colors
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 1.0f, 1.0f, 1.0f
    };

    GLuint _indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    // Create buffers
    GLuint _vbo;
    GLuint _vao;
    GLuint _ebo;

    glGenBuffers( 1, &_vbo );
    glGenBuffers( 1, &_ebo );
    glGenVertexArrays( 1, &_vao );

    glBindVertexArray( _vao );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * 6,
                  _indices, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * 20/*8*//*6*/,
                  _vertices, GL_STATIC_DRAW );

    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 2, GL_FLOAT, 
                           GL_FALSE, sizeof( GLfloat ) * 5, ( void* ) 0 );

    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, 
                           GL_FALSE, sizeof( GLfloat ) * 5, ( void* ) ( sizeof( GLfloat ) * 2 ) );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );

    while ( _window.isActive() )
    {
        _window.clear();
        _window.pollEvents();

        // render loop

        glUseProgram( _programId );
        glBindVertexArray( _vao );

        //glDrawArrays( GL_TRIANGLES, 0, 3 );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

        glBindVertexArray( 0 );

        _window.swapBuffers();
    }

    return 0;
}