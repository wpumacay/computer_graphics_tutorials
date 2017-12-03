

#include "LWindow.h"

#include <iostream>

using namespace std;

void onKeyCallback( int key, int action )
{
    cout << "key callback: " << key << " - action: " << action << endl;
}

void onMouseCallback( int button, int action, double x, double y )
{
    cout << "mousebutton callback: " << x << " - " << y << endl;
}


int main()
{
    engine::LWindow _window;

    _window.registerKeyCallback( onKeyCallback );
    _window.registerMouseCallback( onMouseCallback );

    while ( _window.isActive() )
    {
        _window.clear();
        _window.pollEvents();

        // render loop

        

        _window.swapBuffers();
    }

    return 0;
}