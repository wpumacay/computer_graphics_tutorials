

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
engine::LWindow* g_window;

engine::LSceneRenderer* g_renderer;

#define POINT_A engine::LVec3(  3.0f, 1.0f,  5.0f )
#define POINT_B engine::LVec3( -1.0f, 1.0f, -4.0f )
#define POINT_C engine::LVec3(  3.5f, 1.0f, -2.5f )

#ifdef GLUT_SUPPORT_ENABLED

void _onDefaultViewPoint()
{
    g_scene->resetCamera();
}

void onSubMenuEnableLighting( int optionId )
{
    if ( optionId == 0 )
    {
        g_renderer->disableLighting();
        g_scene->disableLighting();
    }
    else if ( optionId == 1 )
    {
        g_renderer->enableLighting();
        g_scene->enableLighting();
    }
}

void onSubMenuShading( int optionId )
{
    if ( optionId == 0 )
    {
        g_scene->setShadingMode( false );
    }
    else if ( optionId == 1 )
    {
        g_scene->setShadingMode( true );
    }
}

void onSubMenuLighting( int optionId )
{
    if ( optionId == 0 )
    {
        g_scene->setMainPointLightMode( 0 );
        g_scene->setMainSpotLightMode( 1 );
    }
    else if ( optionId == 1 )
    {
        g_scene->setMainPointLightMode( 1 );
        g_scene->setMainSpotLightMode( 0 );
    }
}

void onSubMenuWireframe( int optionId )
{
    if ( optionId == 0 )
    {
        g_scene->getBall()->setWireframeMode( false );
    }
    else if ( optionId == 1 )
    {
        g_scene->getBall()->setWireframeMode( true );
    }
}

void onMainMenuCallback( int optionId )
{
    if ( optionId == 0 )
    {
        _onDefaultViewPoint();
    }
    else if ( optionId == 5 )
    {
        exit( 0 );
    }
}

void onDisplayCallback()
{
    g_window->clear();

    g_scene->update( 0.021 );

    g_renderer->begin( g_scene );
    g_renderer->renderScene( g_scene );
    g_renderer->end( g_scene );
}

#endif

void onKeyCallback( int key, int action )
{
    if ( action == L_KEY_PRESS )
    {
        //cout << "key: " << key << endl;
        //cout << "action: " << action << endl;
        if ( key == L_KEY_W )
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
        else if ( key == L_KEY_S )
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
        else if ( key == L_KEY_R )
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
        else if ( key == L_KEY_L )
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
        else if ( key == L_KEY_X ) { g_scene->increaseCamera( 1.0f, 0.0f, 0.0f ); }
        else if ( key == L_KEY_X_MAYUS ) { g_scene->increaseCamera( -1.0f, 0.0f, 0.0f ); }
        else if ( key == L_KEY_Y ) { g_scene->increaseCamera( 0.0f, 1.0f, 0.0f ); }
        else if ( key == L_KEY_Y_MAYUS ) { g_scene->increaseCamera( 0.0f, -1.0f, 0.0f ); }
        else if ( key == L_KEY_Z ) { g_scene->increaseCamera( 0.0f, 0.0f, 1.0f ); }
        else if ( key == L_KEY_Z_MAYUS ) { g_scene->increaseCamera( 0.0f, 0.0f, -1.0f ); }
    }
}

int main()
{
    g_window = new engine::LWindow();
    g_window->registerKeyCallback( onKeyCallback );

#ifdef GLUT_SUPPORT_ENABLED
    g_window->registerDisplayCallback( onDisplayCallback );
#endif

    glEnable( GL_DEPTH_TEST );

    // Initialize shader manager
    engine::LShaderManager::create();

    g_renderer = new engine::LSceneRenderer();
    g_scene = new hw::LTestScene();
    
    g_renderer->enableLighting();
    g_scene->enableLighting();

#ifdef GLUT_SUPPORT_ENABLED

    // EnableLighting submenu
    auto _smEnableLighting = glutCreateMenu( onSubMenuEnableLighting );
    glutAddMenuEntry( "No", 0 );
    glutAddMenuEntry( "Yes", 1 );
    // Shading submenu
    auto _smShading = glutCreateMenu( onSubMenuShading );
    glutAddMenuEntry( "Flat", 0 );
    glutAddMenuEntry( "Smooth", 1 );
    // Lighting submenu
    auto _smLighting = glutCreateMenu( onSubMenuLighting );
    glutAddMenuEntry( "Spot", 0 );
    glutAddMenuEntry( "Point", 1 );
    // Wireframe submenu
    auto _smWireframe = glutCreateMenu( onSubMenuWireframe );
    glutAddMenuEntry( "No", 0 );
    glutAddMenuEntry( "Yes", 1 );

    glutCreateMenu( onMainMenuCallback );
    glutAddMenuEntry( "Default View Point", 0 );
    glutAddSubMenu( "Enable Lighting", _smEnableLighting );
    glutAddSubMenu( "Shading", _smShading );
    glutAddSubMenu( "Lighting", _smLighting );
    glutAddSubMenu( "Wireframe", _smWireframe );
    glutAddMenuEntry( "Quit", 5 );
    glutAttachMenu( GLUT_LEFT_BUTTON );

    g_window->loop();
#endif

#ifdef GLFW_SUPPORT_ENABLED
    while ( g_window->isActive() )
    {
        g_window->clear();
        g_window->pollEvents();

        g_scene->update( 0.02 );

        g_renderer->begin( g_scene );
        g_renderer->renderScene( g_scene );
        g_renderer->end( g_scene );

        g_window->swapBuffers();
    }
#endif
    return 0;
}