

#include "../Config.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void onKeyCallback( GLFWwindow* pWindow, int key, int scancode,
                    int action, int mode )
{
    cout << "key callback: " << key << " - action: " << action << endl;
}

void onMouseCallback( GLFWwindow* pWindow, int button,
                      int action, int mode )
{
    double _x, _y;
    glfwGetCursorPos( pWindow, &_x, &_y );

    cout << "mousebutton callback: " << _x << " - " << _y << endl;
}

int main()
{
    GLFWwindow* _window;

    int _width;
    int _height;

    // Initialize window and context properties
    glfwInit();
    // Using version 3.3 of opengl -> glsl? ->
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, APP_CONTEXT_VERSION_MAJOR );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, APP_CONTEXT_VERSION_MINOR );
    // Set the context to core, don't enable legacy stuff -> core vs compat?
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    // Disable the window resizable property
    glfwWindowHint( GLFW_RESIZABLE, APP_RESIZABLE );

    // Create the window and get a pointer to it
    _window = glfwCreateWindow( APP_WIDTH,
                                APP_HEIGHT,
                                APP_NAME, NULL, NULL );

    if ( _window == NULL )
    {
        glfwTerminate();
        cout << "ERROR: Couldnt initialize glfw" << endl;
        return -1;
    }

    // This sets the current context to the ...
    // current window's context
    glfwMakeContextCurrent( _window );

    glewExperimental = GL_TRUE;
    if ( glewInit() != GLEW_OK )
    {
        glfwTerminate();
        cout << "couldnt initialize glew, termination required" << endl;
        return -1;
    }

    glfwSetKeyCallback( _window, onKeyCallback );
    glfwSetMouseButtonCallback( _window, onMouseCallback );

    glfwGetFramebufferSize( _window, &_width, &_height );
    glViewport( 0, 0, _width, _height );

    while ( !glfwWindowShouldClose( _window ) )
    {
        glfwPollEvents();

        glClear( GL_COLOR_BUFFER_BIT | 
                 GL_DEPTH_BUFFER_BIT );

        // Do some stuff in here ( RENDER LOOP )

        glfwSwapBuffers( _window );

    }

    return 0;
}