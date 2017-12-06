

#include "LScene.h"
#include "LFixedCamera3d.h"


namespace engine
{


    LScene::LScene()
    {
        m_currentCamera = NULL;
    }

    LScene::~LScene()
    {
        for ( LICamera* _cam : m_cameras )
        {
            delete _cam;
        }

        for ( LILight* _light : m_lights )
        {
            delete _light;
        }

        for ( LEntity* _entity : m_entities )
        {
            delete _entity;
        }

        m_currentCamera = NULL;
    }

    void LScene::update( float dt )
    {
        for ( LEntity* _entity : m_entities )
        {
            _entity->update( dt );
        }
    }

}