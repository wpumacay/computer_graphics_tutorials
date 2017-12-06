

#pragma once

#include "LCommon.h"
#include "LIRenderable.h"
#include "LICamera.h"
#include "LILight.h"
#include "LScene.h"

using namespace std;

namespace engine
{



    class LIRenderer
    {
        protected :

        GLuint m_shader;

        public :

        virtual void render( LIRenderable* renderable ) = 0;
        virtual void renderScene( LScene* pScene ) = 0;
        virtual void begin( LScene* pScene ) = 0;
        virtual void end( LScene* pScene ) = 0;

    };





}

