
/**************************************************************************************************

	Project: Assignment - Path Finding

	   File: MapView.hpp

	 Author: Simon Rybicki

	   Date: 01/02/19

	Version: 1.0

	   Info: Defines map view manager.

**************************************************************************************************/

// Custom include files.
#include "Definitions.hpp"
#include "CVector3cut.hpp"
#include "CMatrix4x4cut.hpp"
#include "Node.hpp"

// Meshes file names.
const string EARTH_MESH = "Earth.x";
const string START_MESH = "Start.x";
const string GOAL_MESH = "Goal.x";
const string CLEAR_MESH = "Clear2.x";
const string WATER_MESH = "Water.x";
const string WOOD_MESH = "Wood.x";
const string WALL_MESH = "Wall.x";

// Scale of a grid square model.
const float MAP_SQUARE_SCALE = 4.0f;

// A collection of terrain square model meshes.
const int TOTAL_GRID_MESHES = 4;

// Minimum path points and total gap points needed for smooth path.
const int MIN_PATH_POINTS = 4;
const int TOTAL_GAP_POINTS = 3;

// Square objects on the map grid.
using Squares = vector<vector<IModel*>>;

// Nodes for each square on the map.
using Nodes = deque<vector<CNode*>>;

class CMapView
{

public:

	// Constructor. Set the the map meshes and intial values for map mid X and Z.
	// Param: Map meshes, Start mesh, Goal mesh, Earth mesh, Node mesh.
	// Return: Map view object.
	CMapView(IMesh* mapMeshCollection[TOTAL_GRID_MESHES], IMesh* startMesh, IMesh* goalMesh,
		     IMesh* earthMesh, IMesh* nodeMesh);

	// Destructor.
	// Param:
	// Return:
	~CMapView();

	// Gets the map mid X value.
	// Param:
	// Return: Mid X position.
	float GetMapMidX();

	// Gets the map mid Z value.
	// Param:
	// Return: Mid Z position.
	float GetMapMidZ();

	// Creates the map squares and node models.
	// Param: Map, Map size.
	// Return:
	void CreateMap(TerrainMap& map, SMapSize& mapSize);

	// Unloads the map squares, nodes and earth.
	// Param: Map, Map size, Start node, Goal node.
	// Return:
	void DestroyMap(TerrainMap& map, SMapSize& mapSize, const SNode* pStartNode, 
		            const SNode* pGoalNode);

	// Creates start and goal squares on the map.
	// Param: Map, Start node, Goal node.
	// Return:
	void CreateCoords(TerrainMap& map, const SNode* pStartNode, const SNode* pGoalNode);

	// Unloads the start and goal squares on the map.
	// Param: Map, Start node, Goal node.
	// Return:
	void DestroyCoords(TerrainMap& map, const SNode* pStartNode, const SNode* pGoalNode);

	// Gets the start mesh.
	// Param:
	// Return: Start mesh.
	IMesh* GetStartMesh();

	// Gets the goal mesh.
	// Param:
	// Return: Goal mesh.
	IMesh* GetGoalMesh();

	// Gets the earth mesh.
	// Param:
	// Return: Earth mesh.
	IMesh* GetEarthMesh();

	// Gets the node mesh.
	// Param:
	// Return: Node mesh.
	IMesh* GetNodeMesh();

	// Gets a mesh from the map meshes.
	// Param: Index of mesh.
	// Return: Map mesh.
	IMesh* GetMapMesh(const int& index);

	// Get the list of node on the open list.
	// Param:
	// Return: Open list nodes.
	vector<CNode*>& GetOpenListMapNodes();

	// Gets the list of node on the closed list.
	// Param:
	// Return: Closed list nodes.
	vector<CNode*>& GetClosedListMapNodes();

	// Gets the list of nodes on the goal path.
	// Param:
	// Return: Path list nodes.
	vector<CNode*>& GetPathListMapNodes();

	// Updates the nodes on the map based on a list of nodes.
	// Param: Map nodes, List nodes.
	// Return:
	void UpdateMapNodes(vector<CNode*>& mapNodes, NodeList& listNodes);

	// Returns a list of nodes on the path to the goal.
	// Param: Path list nodes (data).
	// Return: Path list nodes (map).
	vector<CNode*> GetPathNodes(NodeList& path);

	// Shows the current node on the map.
	// Param: Current node.
	// Return:
	void ShowCurrentNode(const SNode* node);

	// Hides the current node on the map.
	// Param: Current node.
	// Return:
	void HideCurrentNode(const SNode* node);

	// Shows the list of nodes on the map.
	// Param: Map list nodes.
	// Return:
	void ShowNodes(vector<CNode*>& nodes);

	// Hides the list of nodes on the map.
	// Param: Map list nodes.
	// Return:
	void HideNodes(vector<CNode*>& nodes);

	// Reveals the path to the goal.
	// Param:
	// Return:
	void ShowGoalPath();

	// Gets the position of a node on the map.
	// Param: Map node.
	// Return: Node position XYZ.
	CVector3 GetMapNodePosition(const SNode* node);
	
	// Gets a smooth path with lots of points.
	// Param: Path list nodes (map).
	// Return: List of points.
	vector<SPoint> GetSmoothPath(const vector<CNode*>& pathNodes);

	// Gets a normal path with points at every node to the goal.
	// Param: Path list nodes (map).
	// Return: List of points.
	vector<SPoint> GetNormalPath(const vector<CNode*>& pathNodes);

	// Resets the position and colour of nodes on the lists open, closed and goal path.
    // The list items are also cleared.
	// Param:
	// Return:
	void ResetListNodes();

	// Resets the map squares, nodes data, and node lists.
	// Param:
	// Return:
	void ClearData();

private:

	float mMapMidX;
	float mMapMidZ;
	IMesh* mpStartMesh;
	IMesh* mpGoalMesh;
	IMesh* mpEarthMesh;
	IMesh* mpNodeMesh;
	IMesh* mpMapMeshCollection[TOTAL_GRID_MESHES];
	IModel* mpEarth;
	Squares mMapSquares;
	Nodes mMapNodes;
	vector<CNode*> mOpenListMapNodes;
	vector<CNode*> mClosedListMapNodes;
	vector<CNode*> mPathMapNodes;

	// Gets a list of points on the path to the goal.
	// Param: Path list nodes (map).
	// Return: Path list points.
	vector<SPoint> GetPathPoints(const vector<CNode*>& nodes);

	// Gets a list of points on a path that has curves.
	// Param: Path list points.
	// Return: Path list points.
	vector<SPoint> GetCurvePathPoints(const vector<SPoint>& nodes);

	// Creates more points for a path of points.
	// Param: Path list points, New points.
	// Return:
	void CreatePathPoints(vector<SPoint>& path, SPoint* points);

	// Calculates the positions of the extra points added to a path.
	// Param: First point, Second point, Third point, Fourth point, 
	//        New point 1, New point 2, New point 3.
	// Return:
	void QuarterSplines(SPoint point1, SPoint point2, SPoint point3, SPoint point4, 
		                SPoint &quarter, SPoint &half, SPoint &threeQuarter);

};