
#pragma once

#include <GL/glew.h>
#include <iostream>
#include <vector>

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

namespace engine
{

    struct LVec3
    {
        GLfloat x;
        GLfloat y;
        GLfloat z;

        LVec3()
        {
            this->x = 0;
            this->y = 0;
            this->z = 0;        
        }

        LVec3( GLfloat x, GLfloat y, GLfloat z )
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        
        LVec3 operator+( const LVec3& other )
        {
            return LVec3( this->x + other.x,
                              this->y + other.y,
                              this->z + other.z );
        }

        LVec3 operator-( const LVec3& other )
        {
            return LVec3( this->x - other.x,
                              this->y - other.y,
                              this->z - other.z );
        }

        void normalize()
        {
            GLfloat _len = sqrt( x * x + y * y + z * z );
            x = x / _len;
            y = y / _len;
            z = z / _len;
        }

        LVec3 operator*( float s )
        {
            return LVec3( this->x * s,
                              this->y * s,
                              this->z * s );
        }

        void scale( float sx, float sy, float sz )
        {
            x *= sx; y *= sy; z *= sz;
        }

        static LVec3 cross( const LVec3& v1,
                            const LVec3& v2 )
        {
            LVec3 _res;

            _res.x = v1.y * v2.z - v2.y * v1.z;
            _res.y = -v1.x * v2.z + v2.x * v1.z;
            _res.z = v1.x * v2.y - v2.x * v1.y;

            return _res;
        }

    };

    struct LTri
    {
        GLuint i1;
        GLuint i2;
        GLuint i3;
    };

    union LInd3
    {
        GLuint buff[3];
        LTri tri;

        LInd3()
        {
            buff[0] = 0;
            buff[1] = 0;
            buff[2] = 0;
        }

        LInd3( GLuint v1, GLuint v2, GLuint v3 )
        {
            buff[0] = v1;
            buff[1] = v2;
            buff[2] = v3;
        }

        void dump()
        {
            cout << "i1: " << buff[0] << " - i2: " << buff[1] << " - i3: " << buff[2] << endl;
        }
    };




}