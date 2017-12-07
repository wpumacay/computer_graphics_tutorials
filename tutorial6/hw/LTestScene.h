
#pragma once

#include "../LScene.h"
#include "../LFixedCamera3d.h"
#include "../LMesh.h"
#include "../LMaterial.h"
#include "../LMeshBuilder.h"
#include "../LLightDirectional.h"
#include "../LLightPoint.h"
#include "../LLightSpot.h"
#include "../../Config.h"
#include "LBallEntity.h"

using namespace std;
using namespace engine;

namespace hw
{


    class LTestScene : public LScene
    {
        private :

        LBallEntity* m_ballEntity;

        LLightPoint* m_mainPointLight;
        LLightSpot* m_mainSpotLight;


        public :

        LTestScene()
        {
            addCamera( new LFixedCamera3d( LVec3( 7.0f, 3.0f, -10.0f ),
                                           LVec3( -7.0f, -3.0f, 10.0f ),
                                           LVec3( 0.0f, 1.0f, 0.0f ) ) );

            auto _viewMat = m_currentCamera->getViewMatrix();
            auto _invView = glm::inverse( _viewMat );
            auto _invTrans = glm::mat3( _invView );

            //auto _viewRot = glm::mat3( _viewMat );
            //auto _invTrans = glm::transpose( _viewRot );

            glm::vec3 _lightDir = _invTrans * ( glm::vec3( 0.1f, 0.0f, -1.0f ) );
            //cout << "_lightDir: " << glm::to_string( _lightDir ) << endl;
            
            //LVec3 _foo( -7.0f, -3.0f, 10.0f );
            //_foo.normalize();
            //cout << "_foo: " << _foo.toString() << endl;

            addLight( new LLightDirectional( LVec3( 0.0f, 0.0f, 0.0f ),
                                             LVec3( 0.8f, 0.8f, 0.8f ),
                                             LVec3( 0.2f, 0.2f, 0.2f ),
                                             0, LVec3( _lightDir.x, _lightDir.y, _lightDir.z ) ) );
            
            m_mainPointLight = new LLightPoint( LVec3( 0.0f, 0.0f, 0.0f ),
                                                LVec3( 1.0f, 1.0f, 1.0f ),
                                                LVec3( 1.0f, 1.0f, 1.0f ),
                                                0, LVec3( -14.0f, 12.0f, -3.0f ),
                                                2.0f, 0.01f, 0.001f );
            m_mainPointLight->active = 1;
            addLight( m_mainPointLight );
            
            m_mainSpotLight = new LLightSpot( LVec3( 0.0f, 0.0f, 0.0f ),
                                              LVec3( 1.0f, 1.0f, 1.0f ),
                                              LVec3( 1.0f, 1.0f, 1.0f ),
                                              0, LVec3( -14.0f, 12.0f, -3.0f ),
                                              LVec3::normalize( LVec3( -6.0f, 0.0f, -4.5f ) - LVec3( -14.0f, 12.0f, -3.0f ) ),
                                              2.0f, 0.01f, 0.001f, 20.0f, 60.0f );
            m_mainSpotLight->active = 0;
            addLight( m_mainSpotLight );
            
            m_projMatrix = glm::perspective( glm::radians( 45.0f ),
                                             ( float ) APP_WIDTH / APP_HEIGHT,
                                             0.1f, 100.0f );


            LMaterial* _planeMaterial = new LMaterial( LVec3( 0.2f, 0.2f, 0.2f ),
                                                       LVec3( 0.0f, 1.0f, 0.0f ),
                                                       LVec3( 0.0f, 0.0f, 0.0f ),
                                                       LVec3( 0.0f, 1.0f, 0.0f ),
                                                       20.0f );

            LMesh* _planeMesh  = LMeshBuilder::createPlane( 10.0f, 12.0f );

            _planeMesh->setMaterial( _planeMaterial );

            LEntity* _planeEntity = new LEntity( _planeMesh );
            _planeEntity->pos = LVec3( 0.0f, 0.0f, 2.0f );

            m_ballEntity = new LBallEntity( LVec3( 3.0f, 1.0f, 5.0f ) );

            addEntity( m_ballEntity );
            addEntity( _planeEntity );
        }

        LBallEntity* getBall()
        {
            return m_ballEntity;
        }


        void setMainSpotLightMode( int active )
        {
            m_mainSpotLight->active = active;
        }

        void setMainPointLightMode( int active )
        {
            m_mainPointLight->active = active;
        }

    };


}