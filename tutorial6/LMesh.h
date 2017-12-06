
#pragma once

#include "LCommon.h"
#include "LVertexBuffer.h"
#include "LVertexArray.h"
#include "LIndexBuffer.h"
#include "LIRenderable.h"
#include "LMaterial.h"

using namespace std;


namespace engine
{



    class LMesh : public LIRenderable
    {

        private :

        LVertexArray* m_vertexArray;
        LIndexBuffer* m_indexBuffer;
        LMaterial* m_material;

        public :

        LVec3 pos;
        glm::mat4 rotation;
        LVec3 scale;

        LMesh( const vector<LVec3>& vertices, 
               const vector<LVec3>& normals,
               const vector<LInd3>& indices );

        ~LMesh();

        glm::mat4 getModelMatrix() const;

        void setMaterial( LMaterial* pMaterial );
        LMaterial* getMaterial() const { return m_material; }
        LVertexArray* getVertexArray() const { return m_vertexArray; }
        LIndexBuffer* getIndexBuffer() const { return m_indexBuffer; }

        void enableLighting() { m_material->enableLighting(); }
        void disableLighting() { m_material->disableLighting(); }

        void render() override;
    };













}
