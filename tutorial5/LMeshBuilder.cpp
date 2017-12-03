
#include "LMeshBuilder.h"

using namespace std;

namespace engine
{

    LMesh* LMeshBuilder::createBox( GLfloat width, GLfloat height, GLfloat depth )
    {
        LMesh* _mesh = NULL;

        vector<LVec3> _vertices;
        vector<LVec3> _normals;
        vector<LInd3> _indices;

        vector<LVec3> _normalsSource;

        _normalsSource.push_back( LVec3(  0,  0,  1 ) );
        _normalsSource.push_back( LVec3(  0,  0, -1 ) );
        _normalsSource.push_back( LVec3(  0,  1,  0 ) );
        _normalsSource.push_back( LVec3(  0, -1,  0 ) );
        _normalsSource.push_back( LVec3(  1,  0,  0 ) );
        _normalsSource.push_back( LVec3( -1,  0,  0 ) );

        LVec3 _scale( 0.5 * width, 0.5 * height, 0.5 * depth );

        // for each face, compute the vertices that form ...
        // the face perpendicular to that normal
        for ( int q = 0; q < _normalsSource.size(); q++ )
        {
            LVec3 _n = _normalsSource[q];

            // form a tri perpendicular right hand system
            LVec3 _s1 = LVec3( _n.y, _n.z, _n.x );
            LVec3 _s2 = LVec3::cross( _n, _s1 );

            // Add the indices accordingly
            _indices.push_back( LInd3( _vertices.size(),
                                       _vertices.size() + 1,
                                       _vertices.size() + 2 ) );

            _indices.push_back( LInd3( _vertices.size(),
                                       _vertices.size() + 2,
                                       _vertices.size() + 3 ) );

            // Generate each vertex of each face ...
            // according to these vectors
            LVec3 _v;

            _v = _n - _s1 - _s2;
            _v.scale( _scale.x, _scale.y, _scale.z );

            _vertices.push_back( _v );
            _normals.push_back( _n );

            _v = _n - _s1 + _s2;
            _v.scale( _scale.x, _scale.y, _scale.z );

            _vertices.push_back( _v );
            _normals.push_back( _n );

            _v = _n + _s1 + _s2;
            _v.scale( _scale.x, _scale.y, _scale.z );

            _vertices.push_back( _v );
            _normals.push_back( _n );

            _v = _n + _s1 - _s2;
            _v.scale( _scale.x, _scale.y, _scale.z );

            _vertices.push_back( _v );
            _normals.push_back( _n );

        }


        _mesh = new LMesh( _vertices, _normals, _indices );

        return _mesh;
    }
    
    LMesh* LMeshBuilder::createPlane( GLfloat width, GLfloat depth )
    {
        LMesh* _mesh = NULL;

        vector<LVec3> _vertices;
        vector<LVec3> _normals;
        vector<LInd3> _indices;


        LVec3 _n = LVec3( 0.0f, 1.0f, 0.0f );
        LVec3 _s1 = LVec3( 0.0f, 0.0f, 1.0f );
        LVec3 _s2 = LVec3( 1.0f, 0.0f, 0.0f );

        LVec3 _scale = LVec3( 0.5 * width, 0.0f, 0.5 * depth );

        _indices.push_back( LInd3( _vertices.size(),
                                   _vertices.size() + 1,
                                   _vertices.size() + 2 ) );

        _indices.push_back( LInd3( _vertices.size(),
                                   _vertices.size() + 2,
                                   _vertices.size() + 3 ) );

        LVec3 _v;

        _v = _n - _s1 - _s2;
        _v.scale( _scale.x, _scale.y, _scale.z );

        _vertices.push_back( _v );
        _normals.push_back( _n );

        _v = _n - _s1 + _s2;
        _v.scale( _scale.x, _scale.y, _scale.z );

        _vertices.push_back( _v );
        _normals.push_back( _n );

        _v = _n + _s1 + _s2;
        _v.scale( _scale.x, _scale.y, _scale.z );

        _vertices.push_back( _v );
        _normals.push_back( _n );

        _v = _n + _s1 - _s2;
        _v.scale( _scale.x, _scale.y, _scale.z );

        _vertices.push_back( _v );
        _normals.push_back( _n );

        _mesh = new LMesh( _vertices, _normals, _indices );

        return _mesh;
    }


    LMesh* LMeshBuilder::createFromFile( const char* filename )
    {
        LMesh* _mesh = NULL;

        vector<LVec3> _vertices;
        vector<LVec3> _normals;
        vector<LInd3> _indices;

        ifstream _fileHandle( "../res/models/model_sphere_8.obj" );

        string _line;

        getline( _fileHandle, _line );

        int _numFaces = stoi( _line );

        int _indxCounter = 0;

        for ( int q = 0; q < _numFaces; q++ )
        {
            getline( _fileHandle, _line );

            int _numVertices = stoi( _line );

            for ( int p = 0; p < _numVertices; p++ )
            {
                getline( _fileHandle, _line );
                vector<string> _elemns = LMeshBuilder::_split( _line );

                GLfloat _vx = stof( _elemns[0] );
                GLfloat _vy = stof( _elemns[1] );
                GLfloat _vz = stof( _elemns[2] );

                _vertices.push_back( LVec3( _vx, _vy, _vz ) );
                _indices.push_back( LInd3( _indxCounter, 
                                           _indxCounter + 1, 
                                           _indxCounter + 2 ) );
                _indxCounter += 3;
            }

            LVec3 _n = _computeFaceNormal();
        }


        return _mesh;
    }






}