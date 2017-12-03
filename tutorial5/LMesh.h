
#pragma once

#include "LCommon.h"
#include "LVertexBuffer.h"
#include "LVertexArray.h"
#include "LIndexBuffer.h"

using namespace std;


namespace engine
{



    class LMesh
    {

        private :

        LVertexArray* m_vertexArray;
        LIndexBuffer* m_indexBuffer;

        public :

        LVec3 pos;
        LVec3 rot;
        LVec3 scale;

        LMesh( const vector<LVec3>& vertices, 
               const vector<LVec3>& normals,
               const vector<LInd3>& indices );

        ~LMesh();

        glm::mat4 getModelMatrix() const;

        LVertexArray* getVertexArray() const { return m_vertexArray; }
        LIndexBuffer* getIndexBuffer() const { return m_indexBuffer; }

    };













}
