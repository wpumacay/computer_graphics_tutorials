
#pragma once

#include "LScene.h"
#include "LFixedCamera3d.h"
#include "LMesh.h"
#include "LMeshBuilder.h"
#include "LLightDirectional.h"
#include "../Config.h"

using namespace std;

namespace engine
{


    class LTestScene : public LScene
    {



        public :

        LTestScene()
        {
            addCamera( new LFixedCamera3d( LVec3( 7.0f, 3.0f, -10.0f ),
                                           LVec3( -7.0f, -3.0f, 10.0f ),
                                           LVec3( 0.0f, 1.0f, 0.0f ) ) );

            LMesh* _sphereMesh = LMeshBuilder::createFromFile( "../res/models/model_sphere_1024.obj" );
            LMesh* _planeMesh  = LMeshBuilder::createPlane( 10.0f, 10.0f );
            LEntity* _sphereEntity = new LEntity( _sphereMesh );
            LEntity* _planeEntity = new LEntity( _planeMesh );
            _sphereEntity->pos = LVec3( 3.0f, 1.0f, 5.0f );
            _planeMesh->pos = LVec3( 0.0f, 0.0f, 2.0f );

            addEntity( _sphereEntity );
            addEntity( _planeEntity );

            addLight( new LLightDirectional( LVec3( 0.0f, 0.0f, 0.0f ),
                                             LVec3( 0.8f, 0.8f, 0.8f ),
                                             LVec3( 0.2f, 0.2f, 0.2f ),
                                             0, LVec3( 0.0f, -1.0f, 1.0f ) ) );

            m_projMatrix = glm::perspective( glm::radians( 45.0f ),
                                             ( float ) APP_WIDTH / APP_HEIGHT,
                                             0.1f, 100.0f );

        }




    };


}