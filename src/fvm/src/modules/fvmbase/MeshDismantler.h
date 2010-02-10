#ifndef _MESHDISMANTLER_H_
#define _MESHDISMANTLER_H_

#include "Mesh.h"
#include "Array.h"
#include "Vector.h"
#include <vector>
#include <set>
#include <string>
#include <fstream>

class MeshDismantler
{
public:
    
    typedef   shared_ptr< Array<double> >  ArrayDblePtr;
    typedef   shared_ptr< Array<int> >     ArrayIntPtr;
    typedef   map<int,ArrayIntPtr>         ArrayIntPtrMap;
    typedef   map<int, int>                IntMap;
    typedef   shared_ptr< StorageSite >  StorageSitePtr; 
    typedef   shared_ptr< CRConnectivity > CRConnectivityPtr;
    //typedef   shared_ptr< Array<int> >     ArrayIntPtr;
    typedef   shared_ptr< Array<Mesh::VecD3> >   ArrayVecD3Ptr;
    typedef   vector< map<int, set<int> > >      VecMap;
    


   MeshDismantler( const MeshList& meshList );
   ~MeshDismantler();

  //return single mesh, for sake of compatibality we return as meshList
   const MeshList&  meshList() const { return _meshList;}

   void  debug_print();

   //get methods


private:
   MeshDismantler(const MeshDismantler&);
   void  init();

   void setCellsSite();
   void setFacesSite();
   void setNodesSite();
   void setCellsMapper(); 
   void setNodesMapper();
   void setCoord();


   void  setFaceCells();
   void  faceCellsInit( vector<int>& localCellID );
   void  faceCellsAddInteriorFaces( vector<int>& faceID );
   void  faceCellsAddPartitionInterfaces( vector<int>& faceID, vector<int>& localCellID );
   void  faceCellsAddMeshInterfaces     ( vector<int>& faceID, vector<int>& localCellID );
   void  faceCellsAddBoundaryInterfaces ( vector<int>& faceID, vector<int>& localCellID );
   void  faceCellsFinishAdd();

   void  setFaceNodes();
   void  faceNodesInit();
   void  faceNodesAddInteriorFaces( vector<int>& faceID );
   void  faceNodesAddPartitionInterfaces( vector<int>& faceID );
   void  faceNodesAddMeshInterfaces(vector<int>& faceID);
   void  faceNodesAddBoundaryInterfaces( vector<int>& faceID );
   void  faceNodesFinishAdd();



   void  setMesh();  
   void  setSites();
   void  createInteriorFaceGroup();
   void  createInterFaceGroup();
   void  createBoundaryFaceGroup();
   void  createCoords();
   void  createFaceNodes();
   void  createFaceCells();

   void  debug_file_open( const string& fname );
   void  debug_file_close();

    //debug files
   void debug_cell_site();
   void debug_face_site();
   void debug_node_site();
   void debug_cells_mapper();
   void debug_face_cells();
   void debug_nodes_mapper();
   void debug_face_nodes();


   //DATA MEMBERS:
   const Mesh& _mesh;  

   vector<StorageSitePtr> _cellSite;
   vector<StorageSitePtr> _faceSite;
   vector<StorageSitePtr> _nodeSite;
  
  //mappers for inner cells
   vector< ArrayIntPtr >   _localCellToGlobal;   //only inner cells
   vector<int>             _globalCellToMeshID;  //belongs to which mesh from global Cell ID
   vector<int>             _globalCellToLocal;   //only inner cells

   vector < map<int,int> >  _globalToLocalNodes; 
   map<int, ArrayIntPtr >   _localNodeToGlobal; 
   
   vector< multimap<int,int> > _faceIdentifierList;

   vector<CRConnectivityPtr>   _faceCells;
   vector<CRConnectivityPtr>   _faceNodes;
   vector<ArrayVecD3Ptr>       _coord;

   map< int, vector<int> >      _interfaceSize;
   map< int, vector<int> >      _interfaceOffset;
   map< int, vector<int> >      _interfaceID;

   map< int, vector<int> >      _boundarySize;
   map< int, vector<int> >      _boundaryOffset;
   map< int, vector<int> >      _boundaryID;
   map< int,vector<string> >    _boundaryType;

   int  _nInterfaceNodes;
   int  _interiorFaceSize;

   ofstream   _debugFile;
   int        _procID;

   int _nmesh;
   MeshList _meshList;  

};


#endif
