
#pragma once

#include "LCommon.h"

#include "LMesh.h"

#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace engine
{

    struct LMeshBuilder
    {

        private :

        static LVec3 _computeFaceNormal( LVec3 _v1, LVec3 _v2, LVec3 _v3 )
        {
            LVec3 _res;

            LVec3 _v12 = _v2 - _v1;
            LVec3 _v23 = _v3 - _v2;

            _res = LVec3::cross( _v12, _v23 );

            return _res;
        }

        //static void _computeNormalsSingle();
        //static void _computeNormalsAvg();

        vector<string> _split( const string &txt )
        {
            vector<string> _res;
                    
            int pos = txt.find( ' ' );
            if ( pos == std::string::npos )
            {
                _res.push_back( txt );
                return _res;
            }

            int initpos = 0;

            while ( pos != std::string::npos )
            {
                _res.push_back( txt.substr( initpos, pos - initpos + 1 ) );
                initpos = pos + 1;

                pos = txt.find( ' ', initpos );
            }

            _res.push_back( txt.substr( initpos, std::min( pos, (int) txt.size() ) - initpos + 1 ) );
                    
            return _res;
        }

        public :

        static LMesh* createBox( GLfloat width, GLfloat height, GLfloat depth );
        static LMesh* createPlane( GLfloat width, GLfloat depth );
        static LMesh* createFromFile( const char* filename );

    };



}