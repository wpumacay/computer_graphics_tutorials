

#include "LWindow.h"

#include <iostream>

using namespace std;

namespace engine
{

    LWindow* LWindow::INSTANCE = NULL;

#ifdef GLFW_SUPPORT_ENABLED
    LWindow::LWindow()
    {
        if ( LWindow::INSTANCE != NULL )
        {
            delete LWindow::INSTANCE;
        }

        LWindow::INSTANCE = this;
        m_keyCallback = NULL;
        m_mouseCallback = NULL;

        glfwInit();
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, APP_CONTEXT_VERSION_MAJOR );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, APP_CONTEXT_VERSION_MINOR );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        glfwWindowHint( GLFW_RESIZABLE, APP_RESIZABLE );

        m_window = glfwCreateWindow( APP_WIDTH,
                                     APP_HEIGHT,
                                     APP_NAME, NULL, NULL );

        if ( m_window == NULL )
        {
            glfwTerminate();
            cout << "ERROR: Couldnt initialize glfw" << endl;
            m_initialized = false;
            return;
        }

        glfwMakeContextCurrent( m_window );

        glewExperimental = GL_TRUE;
        if ( glewInit() != GLEW_OK )
        {
            glfwTerminate();
            m_initialized = false;
            return;
        }

        glfwSetKeyCallback( m_window, LWindow::onKeyCallback );
        glfwSetMouseButtonCallback( m_window, LWindow::onMouseCallback );

        glfwGetFramebufferSize( m_window, &m_width, &m_height );
        glViewport( 0, 0, m_width, m_height );

        glClearColor( CLEAR_COLOR );
        
        
        m_initialized = true;
    }
#else
    LWindow::LWindow()
    {
        if ( LWindow::INSTANCE != NULL )
        {
            delete LWindow::INSTANCE;
        }

        LWindow::INSTANCE = this;
        m_keyCallback = NULL;
        m_mouseCallback = NULL;
        m_displayCallback = NULL;
        m_idleCallback = NULL;

        int _argc = 0;
        char* _argv;

        glutInit( &_argc, &_argv );
        glutInitWindowSize( APP_WIDTH, APP_HEIGHT );
        glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
        glutCreateWindow( APP_NAME );

        glewExperimental = GL_TRUE;
        if ( glewInit() != GLEW_OK )
        {
            cout << "ERROR: Couldnt initialize GLEW" << endl;
            m_initialized = false;
            return;
        }

        glutDisplayFunc( LWindow::onDisplayCallback );
        glutIdleFunc( LWindow::onIdleCallback );

        glutMouseFunc( LWindow::onMouseCallback );
        glutKeyboardFunc( LWindow::onKeyCallback );

        glClearColor( CLEAR_COLOR );
        
        
        m_initialized = true;
    }
#endif

    LWindow::~LWindow()
    {
        release();
    }

    void LWindow::loop()
    {
    #ifdef GLUT_SUPPORT_ENABLED
        glutMainLoop();
    #endif
    }

    void LWindow::release()
    {
#ifdef GLFW_SUPPORT_ENABLED
        m_window = NULL;
        glfwTerminate();
#endif
    }

#ifdef GLFW_SUPPORT_ENABLED
    void LWindow::onKeyCallback( GLFWwindow* pWindow, int key, 
                                 int scancode, int action, int mode )
    {
        if ( LWindow::INSTANCE->m_keyCallback == NULL )
        {
            return;
        }

        LWindow::INSTANCE->m_keyCallback( key, action );
    }

    void LWindow::onMouseCallback( GLFWwindow* pWindow, int button, 
                                   int action, int mode )
    {
        if ( LWindow::INSTANCE->m_mouseCallback == NULL )
        {
            return;
        }
        
        double _x, _y;
        glfwGetCursorPos( pWindow, &_x, &_y );

        LWindow::INSTANCE->m_mouseCallback( button, action, _x, _y );
    }
#else
    void LWindow::onKeyCallback( unsigned char key, int x, int y )
    {
        if ( LWindow::INSTANCE->m_keyCallback == NULL )
        {
            return;
        }

        LWindow::INSTANCE->m_keyCallback( key, L_KEY_PRESS );
    }

    void LWindow::onMouseCallback( int button, int action, int x, int y )
    {
        if ( LWindow::INSTANCE->m_mouseCallback == NULL )
        {
            return;
        }

        LWindow::INSTANCE->m_mouseCallback( button, action, (double)x, (double)y );
    }

    void LWindow::onDisplayCallback()
    {
        if ( LWindow::INSTANCE->m_displayCallback == NULL )
        {
            return;
        }

        LWindow::INSTANCE->m_displayCallback();

        glutSwapBuffers();
    }

    void LWindow::onIdleCallback()
    {
        glutPostRedisplay();
    }


#endif
    void LWindow::registerKeyCallback( FnPtr_keyboard_callback callback )
    {
        m_keyCallback = callback;
    }

    void LWindow::registerMouseCallback( FnPtr_mouse_callback callback )
    {
        m_mouseCallback = callback;
    }
#ifdef GLUT_SUPPORT_ENABLED
    void LWindow::registerDisplayCallback( FnPtr_display_callback callback )
    {
        m_displayCallback = callback;
    }

    void LWindow::registerIdleCallback( FnPtr_idle_callback callback )
    {
        m_idleCallback = callback;
    }
#endif
}