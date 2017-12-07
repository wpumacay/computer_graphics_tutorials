
#pragma once


#include "../LMeshBuilder.h"
#include "../LEntity.h"
#include "../LMeshComponent.h"
#include "LBallMovementComponent.h"

using namespace std;
using namespace engine;

namespace hw
{


    class LBallEntity : public LEntity
    {

        private :

        vector<LVec3> m_path;

        bool m_motionStarted;

        LVec3 m_start;
        int m_currentPathIndx;

        public :

        LBallEntity( const LVec3& start ) : LEntity()
        {
            LMaterial* _sphereMaterial = new LMaterial( LVec3( 0.2f, 0.20f, 0.2f ),
                                                        LVec3( 1.0f, 0.84f, 0.0f ),
                                                        LVec3( 1.0f, 0.84f, 0.0f ),
                                                        LVec3( 1.0f, 0.84f, 0.0f ),
                                                        125.0f );

            LMesh* _sphereMesh = LMeshBuilder::createFromFile( "../res/models/model_sphere_1024.obj" );

            _sphereMesh->setMaterial( _sphereMaterial );

            addComponent( new LMeshComponent( this, _sphereMesh ) );
            addComponent( new LBallMovementComponent( this, 2 * _PI * 0.25, 1 ) );

            this->pos = start;
            m_start = start;

            m_motionStarted = false;
            m_currentPathIndx = 0;
        }


        void setWireframeMode( bool isWireframe )
        {
            auto _meshComponent = getComponent<LMeshComponent>();
            _meshComponent->getMesh()->drawAsWireframe = isWireframe;
        }

        void startSampleMotion( const vector<LVec3>& path )
        {
            m_path = path;
            this->pos = m_path[0];

            auto _movComponent = getComponent<LBallMovementComponent>();
            _movComponent->moveTo( m_path[1], LVec3( 0.0f, 1.0f, 0.0f ) );

            m_motionStarted = true;
            m_currentPathIndx = 1;
        }

        void resetPosition()
        {
            this->pos = m_start;
            m_motionStarted = false;
            m_currentPathIndx = 0;

            auto _movComponent = getComponent<LBallMovementComponent>();
            _movComponent->stop();

            m_path.clear();
        }

        void stopMovement()
        {
            m_motionStarted = false;
            auto _movComponent = getComponent<LBallMovementComponent>();
            _movComponent->stop();            
        }

        void resumeMovement()
        {
            m_motionStarted = true;
            auto _movComponent = getComponent<LBallMovementComponent>();
            _movComponent->resume();            
        }

        void update( float dt ) override
        {
            LEntity::update( dt );

            if ( m_motionStarted )
            {
                auto _movComponent = getComponent<LBallMovementComponent>();
                if ( !_movComponent->isMoving() )
                {
                    // If has stopped, then go to the next point
                    if ( m_currentPathIndx < m_path.size() - 1 )
                    {
                        m_currentPathIndx++;
                        _movComponent->moveTo( m_path[m_currentPathIndx], LVec3( 0.0f, 1.0f, 0.0f ) );
                    }
                    else
                    {
                        m_motionStarted = false;
                        m_currentPathIndx = 0;
                    }
                }
            }
        }

        bool hasMotionStarted() { return m_motionStarted; }

    };






}
