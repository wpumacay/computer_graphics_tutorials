

#pragma once

#include "../Common.h"

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

namespace engine
{

    struct LShaderManager
    {

        private :

        LShaderManager();

        public :

        map< string, GLuint > programs;

        static LShaderManager* INSTANCE;

        static void create();
        ~LShaderManager();
        void release();

        GLuint createShader( const char* filename, int shaderType );
        GLuint createProgram( GLuint vShader, GLuint fShader );


    };

}