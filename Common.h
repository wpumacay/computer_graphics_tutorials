

#pragma once

typedef void ( *FnPtr_keyboard_callback )( int key, int action );
typedef void ( *FnPtr_mouse_callback )( int button, int action, double x, double y );
typedef void ( *FnPtr_display_callback )();
typedef void ( *FnPtr_idle_callback )();