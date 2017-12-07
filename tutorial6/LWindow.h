

#pragma once

#include "../Config.h"
#include "../Common.h"

#define GLEW_STATIC
#include <GL/glew.h>

#ifndef GLFW_SUPPORT_ENABLED
    #include <GL/glut.h>
#else
    #include <GLFW/glfw3.h>
#endif
#include "LInputDefinitions.h"

#define CLEAR_COLOR 0.529f, 0.807f, 0.92f, 1.0f

namespace engine
{

    class LWindow
    {


        private :

        static LWindow* INSTANCE;
#ifdef GLFW_SUPPORT_ENABLED
        GLFWwindow* m_window;
#endif
        int m_width;
        int m_height;

        FnPtr_keyboard_callback m_keyCallback;
        FnPtr_mouse_callback m_mouseCallback;
#ifndef GLFW_SUPPORT_ENABLED
        FnPtr_display_callback m_displayCallback;
        FnPtr_idle_callback m_idleCallback;
#endif

        bool m_initialized;

        public :

        LWindow();
        ~LWindow();
        void release();

        void loop();

#ifdef GLFW_SUPPORT_ENABLED
        static void onKeyCallback( GLFWwindow* pWindow, int key, 
                                   int scancode, int action, int mode );

        static void onMouseCallback( GLFWwindow* pWindow, int button, 
                                     int action, int mode );
#else
        static void onKeyCallback( unsigned char key, int x, int y );
        static void onMouseCallback( int button, int action, int x, int y );
        static void onDisplayCallback();
        static void onIdleCallback();
#endif

        void registerKeyCallback( FnPtr_keyboard_callback callback );
        void registerMouseCallback( FnPtr_mouse_callback callback );
#ifdef GLUT_SUPPORT_ENABLED        
        void registerDisplayCallback( FnPtr_display_callback callback );
        void registerIdleCallback( FnPtr_idle_callback callback );
#endif
        void clear() { glClear( GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT ); }

        void pollEvents() 
        { 
        #ifdef GLFW_SUPPORT_ENABLED
            glfwPollEvents();
        #endif
        }

        void swapBuffers() 
        { 
        #ifdef GLFW_SUPPORT_ENABLED
            glfwSwapBuffers( m_window ); 
        #endif
        }

        bool isActive() 
        { 
        #ifdef GLFW_SUPPORT_ENABLED
            return glfwWindowShouldClose( m_window ) == 0; 
        #else
            return true;
        #endif
        }

        bool isInitialized() { return m_initialized; }

        int width() { return m_width; }
        int height() { return m_height; }

    };










}