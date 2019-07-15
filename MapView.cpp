
/**************************************************************************************************

	Project: Assignment - Path Finding

	   File: MapView.cpp

	 Author: Simon Rybicki

	   Date: 01/02/19

	Version: 1.0

	   Info: Implements map view manager.

**************************************************************************************************/

#include "MapView.hpp"

// Constructor. Set the the map meshes and intial values for map mid X and Z.
CMapView::CMapView(IMesh* pMapMeshCollection[TOTAL_GRID_MESHES], IMesh* pStartMesh, IMesh* pGoalMesh,
	               IMesh* pEarthMesh, IMesh* pNodeMesh)
{
	for (int i = 0; i < TOTAL_GRID_MESHES; ++i)
	{
		mpMapMeshCollection[i] = pMapMeshCollection[i];
	}

	mpStartMesh = pStartMesh;
	mpGoalMesh = pGoalMesh;
	mpEarthMesh = pEarthMesh;
	mpNodeMesh = pNodeMesh;

	mMapMidX = 0.0f;
	mMapMidZ = 0.0f;
}

// Destructor.
CMapView::~CMapView() 
{
	for (auto& row : mMapNodes)
	{
		for (auto& col : row)
		{
			delete col;
		}
	}
}

// Gets the map mid X value.
float CMapView::GetMapMidX()
{
	return mMapMidX;
}

// Gets the map mid Z value.
float CMapView::GetMapMidZ()
{
	return mMapMidZ;
}

// Creates the map squares and node models.
void CMapView::CreateMap(TerrainMap& map, SMapSize& mapSize)
{
	// Update map mid X and Z values.
	mMapMidX = (mapSize.mWidth * MAP_SQUARE_SCALE);
	mMapMidZ = (mapSize.mHeight * MAP_SQUARE_SCALE);

	// Setup model positioning values.
	float step = (MAP_SQUARE_SCALE * 2.0f);
	float startPosX = MAP_SQUARE_SCALE;

	// Set adjustable position initial values.
	float nextPosX = startPosX;
	float nextPosZ = MAP_SQUARE_SCALE;

	vector<ETerrainCost> mapRow;
	vector<IModel*> squareRow;
	vector<CNode*> nodeRow;
	ETerrainCost tCost;

	// Create grid terrain objects.
	for (int row = 0; row < mapSize.mHeight; ++row)
	{
		mapRow = map[row];

		for (int col = 0; col < mapSize.mWidth; ++col)
		{
			tCost = mapRow[col];

			squareRow.push_back(mpMapMeshCollection[tCost]->CreateModel(nextPosX, 0.0f, nextPosZ));
			nodeRow.push_back(new CNode(mpNodeMesh, nextPosX, NODE_HIDE_POS_Y, nextPosZ));
			nextPosX += step;
		}

		mMapSquares.push_back(squareRow);
		mMapNodes.push_back(nodeRow);
		squareRow.clear();
		nodeRow.clear();

		nextPosX = startPosX;
		nextPosZ += step;
	}

	// Create earth object.
	// Position the earth object to be in the middle of the grid map.
	// Set correct scale to be the same size as map grid.
	mpEarth = mpEarthMesh->CreateModel(mMapMidX, 0.0f, mMapMidZ);
	mpEarth->ScaleX(mapSize.mWidth);
	mpEarth->ScaleZ(mapSize.mHeight);
}

// Unloads the map squares, nodes and earth.
void CMapView::DestroyMap(TerrainMap& map, SMapSize& mapSize, const SNode* pStartNode, 
	                      const SNode* pGoalNode)
{
	int nodeStartPosX = pStartNode->mX;
	int nodeStartPosY = pStartNode->mY;
	int nodeGoalPosX = pGoalNode->mX;
	int nodeGoalPosY = pGoalNode->mY;

	ETerrainCost tCost;

	// Remove all map square and node models.
	for (int row = 0; row < mapSize.mHeight; ++row)
	{
		for (int col = 0; col < mapSize.mWidth; ++col)
		{
			tCost = map[row][col];

			mpMapMeshCollection[tCost]->RemoveModel(mMapSquares[row][col]);
			mpNodeMesh->RemoveModel(mMapNodes[row][col]->GetModel());
		}
	}

	mpEarthMesh->RemoveModel(mpEarth);
}

// Creates start and goal squares on the map.
void CMapView::CreateCoords(TerrainMap& map, const SNode* pStartNode, const SNode* pGoalNode)
{
	int startX = pStartNode->mX;
	int startY = pStartNode->mY;
	int goalX = pGoalNode->mX;
	int goalY = pGoalNode->mY;

	float tPosX, tPosZ;
	ETerrainCost tCost;

	tPosX = mMapSquares[startY][startX]->GetX();
	tPosZ = mMapSquares[startY][startX]->GetZ();
	tCost = map[startY][startX];

	mpMapMeshCollection[tCost]->RemoveModel(mMapSquares[startY][startX]);
	mMapSquares[startY][startX] = mpStartMesh->CreateModel(tPosX, 0.0f, tPosZ);

	tPosX = mMapSquares[goalY][goalX]->GetX();
	tPosZ = mMapSquares[goalY][goalX]->GetZ();
	tCost = map[goalY][goalX];

	mpMapMeshCollection[tCost]->RemoveModel(mMapSquares[goalY][goalX]);
	mMapSquares[goalY][goalX] = mpGoalMesh->CreateModel(tPosX, 0.0f, tPosZ);
}

// Unloads the start and goal squares on the map.
void CMapView::DestroyCoords(TerrainMap& map, const SNode* pStartNode, const SNode* pGoalNode)
{
	int startX = pStartNode->mX;
	int startY = pStartNode->mY;
	int goalX = pGoalNode->mX;
	int goalY = pGoalNode->mY;

	float tPosX, tPosZ;
	ETerrainCost tCost;

	tPosX = mMapSquares[startY][startX]->GetX();
	tPosZ = mMapSquares[startY][startX]->GetZ();
	tCost = map[startY][startX];

	mpStartMesh->RemoveModel(mMapSquares[startY][startX]);
	mMapSquares[startY][startX] = mpMapMeshCollection[tCost]->CreateModel(tPosX, 0.0f, tPosZ);

	tPosX = mMapSquares[goalY][goalX]->GetX();
	tPosZ = mMapSquares[goalY][goalX]->GetZ();
	tCost = map[goalY][goalX];

	mpGoalMesh->RemoveModel(mMapSquares[goalY][goalX]);
	mMapSquares[goalY][goalX] = mpMapMeshCollection[tCost]->CreateModel(tPosX, 0.0f, tPosZ);
}

// Gets the start mesh.
IMesh* CMapView::GetStartMesh()
{
	return mpStartMesh;
}

// Gets the goal mesh.
IMesh* CMapView::GetGoalMesh()
{
	return mpGoalMesh;
}

// Gets the earth mesh.
IMesh* CMapView::GetEarthMesh()
{
	return mpEarthMesh;
}

// Gets the node mesh.
IMesh* CMapView::GetNodeMesh()
{
	return mpNodeMesh;
}

// Gets a mesh from the map meshes.
IMesh* CMapView::GetMapMesh(const int& index)
{
	return mpMapMeshCollection[index];
}

// Get the list of node on the open list.
vector<CNode*>& CMapView::GetOpenListMapNodes()
{
	return mOpenListMapNodes;
}

// Gets the list of node on the closed list.
vector<CNode*>& CMapView::GetClosedListMapNodes()
{
	return mClosedListMapNodes;
}

// Gets the list of nodes on the goal path.
vector<CNode*>& CMapView::GetPathListMapNodes()
{
	return mPathMapNodes;
}

// Updates the nodes on the map based on a list of nodes.
void CMapView::UpdateMapNodes(vector<CNode*>& mapNodes, NodeList& listNodes)
{
	mapNodes.clear();

	for (const auto &node : listNodes)
	{
		mapNodes.push_back(mMapNodes[node->mY][node->mX]);
	}
}

// Returns a list of nodes on the path to the goal.
vector<CNode*> CMapView::GetPathNodes(NodeList& path)
{
	vector<CNode*> pathNodes;

	for (auto node = path.begin(); node != path.end(); ++node)
	{
		pathNodes.push_back(mMapNodes[(*node)->mY][(*node)->mX]);
	}

	return pathNodes;
}

// Shows the current node on the map.
void CMapView::ShowCurrentNode(const SNode* node)
{
	mMapNodes[node->mY][node->mX]->SetColour(NODE_RED_TEX);
}

// Hides the current node on the map.
void CMapView::HideCurrentNode(const SNode* node)
{
	mMapNodes[node->mY][node->mX]->SetColour(NODE_BLUE_TEX);
}

// Shows the list of nodes on the map.
void CMapView::ShowNodes(vector<CNode*>& nodes)
{
	for (auto node = nodes.begin(); node != nodes.end(); ++node)
	{
		(*node)->Show();
	}
}

// Hides the list of nodes on the map.
void CMapView::HideNodes(vector<CNode*>& nodes)
{
	for (auto node = nodes.begin(); node != nodes.end(); ++node)
	{
		(*node)->Hide();
	}
}

// Reveals the path to the goal.
void CMapView::ShowGoalPath()
{
	for (auto node = mPathMapNodes.begin(); node != mPathMapNodes.end(); ++node)
	{
		(*node)->Show();
		(*node)->SetColour(NODE_RED_TEX);
	}
}

// Gets the position of a node on the map.
CVector3 CMapView::GetMapNodePosition(const SNode* node)
{
	return CVector3(mMapNodes[node->mY][node->mX]->GetPosX(),
					mMapNodes[node->mY][node->mX]->GetPosY(),
					mMapNodes[node->mY][node->mX]->GetPosZ());
}

// Gets a smooth path with lots of points.
vector<SPoint> CMapView::GetSmoothPath(const vector<CNode*>& pathNodes)
{
	vector<SPoint> path1 = GetPathPoints(pathNodes);
	vector<SPoint> path2 = GetCurvePathPoints(path1);
	vector<SPoint> path3 = GetCurvePathPoints(path2);

	return path3;
}

// Gets a normal path with points at every node to the goal.
vector<SPoint> CMapView::GetNormalPath(const vector<CNode*>& pathNodes)
{
	vector<SPoint> path;

	for (const auto& node : pathNodes)
	{
		SPoint point = { node->GetPosX(), node->GetPosY(), node->GetPosZ() };
		path.push_back(point);
	}

	return path;
}

// Resets the position and colour of nodes on the lists open, closed and goal path.
// The list items are also cleared.
void CMapView::ResetListNodes()
{
	for (auto node = mOpenListMapNodes.begin(); node != mOpenListMapNodes.end(); ++node)
	{
		(*node)->Hide();
		(*node)->SetColour(NODE_BLUE_TEX);
	}
	mOpenListMapNodes.clear();

	for (auto node = mClosedListMapNodes.begin(); node != mClosedListMapNodes.end(); ++node)
	{
		(*node)->Hide();
		(*node)->SetColour(NODE_BLUE_TEX);
	}
	mClosedListMapNodes.clear();

	for (auto node = mPathMapNodes.begin(); node != mPathMapNodes.end(); ++node)
	{
		(*node)->Hide();
		(*node)->SetColour(NODE_BLUE_TEX);
	}
	mPathMapNodes.clear();
}

// Resets the map squares, nodes data, and node lists.
void CMapView::ClearData()
{
	mMapSquares.clear();

	for (auto& row : mMapNodes)
	{
		for (auto& col : row) 
		{
			delete col;
		}
	}
	mMapNodes.clear();

	mOpenListMapNodes.clear();
	mClosedListMapNodes.clear();
	mPathMapNodes.clear();
}

// Gets a list of points on the path to the goal.
vector<SPoint> CMapView::GetPathPoints(const vector<CNode*>& nodes)
{
	vector<SPoint> path;

	for (const auto& node : nodes)
	{
		SPoint point = { node->GetPosX(), 0.0f, node->GetPosZ() };
		path.push_back(point);
	}

	return path;
}

// Gets a list of points on a path that has curves.
vector<SPoint> CMapView::GetCurvePathPoints(const vector<SPoint>& nodes)
{
	vector<SPoint> path;
	SPoint points[TOTAL_GAP_POINTS];

	const int totalPathNodes = static_cast<int>(nodes.size());

	QuarterSplines(nodes[0], nodes[0], nodes[1], nodes[2], points[0], points[1], points[2]);
	path.push_back(nodes[0]);
	CreatePathPoints(path, points);

	for (int i = 0; i <= (totalPathNodes - MIN_PATH_POINTS); ++i)
	{
		QuarterSplines(nodes[i], nodes[i + 1], nodes[i + 2], nodes[i + 3], points[0], points[1], points[2]);
		path.push_back(nodes[i + 1]);
		CreatePathPoints(path, points);
	}

	QuarterSplines(nodes[totalPathNodes - 3], nodes[totalPathNodes - 2], nodes[totalPathNodes - 1], nodes[totalPathNodes - 1], points[0], points[1], points[2]);
	path.push_back(nodes[totalPathNodes - 2]);
	CreatePathPoints(path, points);
	path.push_back(nodes[totalPathNodes - 1]);

	return path;
}

// Creates more points for a path of points.
void CMapView::CreatePathPoints(vector<SPoint>& path, SPoint* points)
{
	for (int i = 0; i < TOTAL_GAP_POINTS; ++i)
	{
		points[i].mY = 0.0f;
		path.push_back(points[i]);
	}
}

// Calculates the positions of the extra points added to a path.
void CMapView::QuarterSplines(SPoint point1, SPoint point2, SPoint point3, SPoint point4, 
	                          SPoint &quarter, SPoint &half, SPoint &threeQuarter)
{
	// Calculate a quarter of the way along the set of points.
	quarter.mX = (point1.mX * -0.0703125f) + (point2.mX * 0.8671875f) + (point3.mX * 0.2265625f) + (point4.mX * -0.0234375f);
	quarter.mZ = (point1.mZ * -0.0703125f) + (point2.mZ * 0.8671875f) + (point3.mZ * 0.2265625f) + (point4.mZ * -0.0234375f);

	// Calculate a half of the way along the set of points.
	half.mX = (point1.mX * -0.0625f) + (point2.mX * 0.5625f) + (point3.mX * 0.5625f) + (point4.mX * -0.0625f);
	half.mZ = (point1.mZ * -0.0625f) + (point2.mZ * 0.5625f) + (point3.mZ * 0.5625f) + (point4.mZ * -0.0625f);

	// Calculate three-quarters of the way along the set of points.
	threeQuarter.mX = (point1.mX * -0.0234375f) + (point2.mX * 0.2265625f) + (point3.mX * 0.8671875f) + (point4.mX * -0.0703125f);
	threeQuarter.mZ = (point1.mZ * -0.0234375f) + (point2.mZ * 0.2265625f) + (point3.mZ * 0.8671875f) + (point4.mZ * -0.0703125f);
}