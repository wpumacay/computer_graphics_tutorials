
#pragma once

#include "LCommon.h"

#include "LMesh.h"

namespace engine
{

    struct LMeshBuilder
    {

        private :

        //static void _computeFaceNormal();
        //static void _computeNormalsSingle();
        //static void _computeNormalsAvg();

        public :

        static LMesh* createBox( GLfloat width, GLfloat height, GLfloat depth );
        static LMesh* createPlane( GLfloat width, GLfloat depth );
        //static LMesh* createFromFile( const char* filename );

    };



}