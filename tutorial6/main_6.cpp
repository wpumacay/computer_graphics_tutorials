

#include "LWindow.h"
#include "LShaderManager.h"
#include "LSceneRenderer.h"
#include "LTestScene.h"

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

    engine::LSceneRenderer* _renderer = new engine::LSceneRenderer();
    //_renderer->enableLighting();
    engine::LTestScene* _scene = new engine::LTestScene();

    while ( _window.isActive() )
    {
        _window.clear();
        _window.pollEvents();

        _scene->update( 0.02 );

        _renderer->begin( _scene );
        _renderer->renderScene( _scene );
        _renderer->end( _scene );

        _window.swapBuffers();
    }

    return 0;
}