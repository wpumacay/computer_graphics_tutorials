

#include "LWindow.h"
#include "LShaderManager.h"
#include "LSceneRenderer.h"
#include "hw/LTestScene.h"

#include <iostream>
#include <vector>

using namespace std;

bool g_isWireframe = false;
bool g_isMainPointLightActive = true;
hw::LTestScene* g_scene;

engine::LSceneRenderer* g_renderer;

#define POINT_A engine::LVec3(  3.0f, 1.0f,  5.0f )
#define POINT_B engine::LVec3( -1.0f, 1.0f, -4.0f )
#define POINT_C engine::LVec3(  3.5f, 1.0f, -2.5f )

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
                g_scene->getBall()->setWireframeMode( true );
                g_renderer->disableLighting();
                g_scene->disableLighting();
            }
            else
            {
                cout << "changed to fill" << endl;
                g_scene->getBall()->setWireframeMode( false );
                g_renderer->enableLighting();
                g_scene->enableLighting();
            }
        }
        else if ( key == GLFW_KEY_S )
        {
            auto _ball = g_scene->getBall();

            if ( _ball->hasMotionStarted() )
            {
                _ball->stopMovement();
            }
            else
            {
                _ball->resumeMovement();
            }
        }
        else if ( key == GLFW_KEY_R )
        {
            auto _ball = g_scene->getBall();

            if ( _ball->hasMotionStarted() )
            {
                _ball->resetPosition();
            }
            else
            {
                vector<engine::LVec3> _path;
                _path.push_back( POINT_A );
                _path.push_back( POINT_B );
                _path.push_back( POINT_C );
                _path.push_back( POINT_A );

                _ball->startSampleMotion( _path );
            }
        }
        else if ( key == GLFW_KEY_L )
        {
            g_isMainPointLightActive = !g_isMainPointLightActive;
            if ( g_isMainPointLightActive )
            {
                g_scene->setMainPointLightMode( 1 );
                g_scene->setMainSpotLightMode( 0 );
            }
            else
            {
                g_scene->setMainPointLightMode( 0 );
                g_scene->setMainSpotLightMode( 1 );
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

    g_renderer = new engine::LSceneRenderer();
    g_scene = new hw::LTestScene();
    
    g_renderer->enableLighting();
    g_scene->enableLighting();

    while ( _window.isActive() )
    {
        _window.clear();
        _window.pollEvents();

        g_scene->update( 0.02 );

        g_renderer->begin( g_scene );
        g_renderer->renderScene( g_scene );
        g_renderer->end( g_scene );

        _window.swapBuffers();
    }

    return 0;
}