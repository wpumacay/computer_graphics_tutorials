

#include "LMesh.h"

using namespace std;

namespace engine
{


    LMesh::LMesh( const vector<LVec3>& vertices, 
                  const vector<LVec3>& normals,
                  const vector<LInd3>& indices )
    {
        LVertexBuffer* _vBuffer = new LVertexBuffer();
        _vBuffer->setData( sizeof( LVec3 ) * vertices.size(),
                           3, vertices.data() );

        LVertexBuffer* _nBuffer = new LVertexBuffer();
        _nBuffer->setData( sizeof( LVec3 ) * normals.size(),
                           3, normals.data() );

        m_vertexArray = new LVertexArray();
        m_vertexArray->addBuffer( _vBuffer, 0 );
        m_vertexArray->addBuffer( _nBuffer, 1 );

        m_indexBuffer = new LIndexBuffer();
        m_indexBuffer->setData( sizeof( LInd3 ) * indices.size(), 
                                3 * indices.size(), indices.data() );

        scale = LVec3( 1.0f, 1.0f, 1.0f );
    }


    LMesh::~LMesh()
    {
        delete m_vertexArray;
        delete m_indexBuffer;
    }

    void LMesh::getModelMatrix()
    {
        glm::mat4 _model = glm::mat4( 1.0f );

        _model = glm::scale( _model, glm::vec3( scale.x, scale.y, scale.z ) );
        _model = glm::rotate( _model, glm::radians( rot.x ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
        _model = glm::rotate( _model, glm::radians( rot.y ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
        _model = glm::rotate( _model, glm::radians( rot.z ), glm::vec3( 0.0f, 0.0f, 1.0f ) );
        _model = glm::translate( _model, glm::vec3( pos.x, pos.y, pos.z ) );

        return _model;
    }
}