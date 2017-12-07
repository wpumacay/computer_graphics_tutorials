

#include "../LComponent.h"

using namespace std;
using namespace engine;

#define ARRIVAL_TOLERANCE 0.1

namespace hw
{

    class LBallMovementComponent : public LComponent
    {
        private :

        float m_rollingAngularSpeed;
        float m_ballRadius;
        float m_rollingLinearSpeed;

        LVec3 m_current;
        LVec3 m_target;
        LVec3 m_tdir;
        LVec3 m_ndir;

        glm::mat4 m_rotation;

        bool m_isMoving;

        bool _isNearDestination()
        {
            LVec3 _delta = m_target - m_current;

            if ( _delta.length() < ARRIVAL_TOLERANCE )
            {
                return true;
            }

            return false;
        }

        public :

        LBallMovementComponent( LEntity* pEntity, 
                                float rollingSpeed, 
                                float ballRadius ) : LComponent( pEntity )
        {
            m_rollingAngularSpeed = rollingSpeed;
            m_ballRadius = ballRadius;
            m_rollingLinearSpeed = m_ballRadius * m_rollingAngularSpeed;

            type = LBallMovementComponent::getStaticType();

            m_rotation = m_entity->rotation;
        }

        static string getStaticType() { return string( "ballmovement" ); }

        void stop()
        {
            m_isMoving = false;
        }

        void resume()
        {
            m_isMoving = true;
        }

        void moveTo( const LVec3& target, const LVec3& up )
        {
            m_target = target;
            m_current = m_entity->pos;
            m_rotation = m_entity->rotation;

            m_tdir = LVec3::normalize( m_target - m_current );
            m_ndir = LVec3::normalize( LVec3::cross( m_tdir, up ) );

            m_isMoving = true;
        }

        void update( float dt )
        {
            if ( !m_isMoving )
            {
                return;
            }

            LVec3 _disp = m_tdir * ( m_rollingLinearSpeed * dt );
            m_current = m_current + _disp;

            float _dtheta = -m_rollingAngularSpeed * dt;
            glm::mat4 _rot = glm::rotate( _dtheta, glm::vec3( m_ndir.x, m_ndir.y, m_ndir.z ) );
            m_rotation = _rot * m_rotation;

            //cout << "_dtheta: " << _dtheta << endl;
            //cout << "ndir: " << m_ndir.toString() << endl;

            m_entity->rotation = m_rotation;
            m_entity->pos = m_current;

            if ( _isNearDestination() )
            {
                m_isMoving = false;
            }
        }

        bool isMoving() { return m_isMoving; }

    };





}