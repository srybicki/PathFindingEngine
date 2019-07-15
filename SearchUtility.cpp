
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: SearchUtility.cpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Implements useful methods used by search algorithms.

**************************************************************************************************/

#include "SearchUtility.hpp"

// Displays the map and shows cost of each grid square.
void CSearchUtility::DisplayMap(TerrainMap& map, SMapSize& mapSize, SNode* pStartNode,
	                            SNode* pGoalNode)
{
	cout << "\n " << mapSize.mWidth << "x" << mapSize.mHeight << " Map:" << "\n\n";

	for (int rowIndex = (mapSize.mHeight - 1); rowIndex >= 0; --rowIndex)
	{
		cout << " " << rowIndex << " |";

		for (int colIndex = 0; colIndex < mapSize.mWidth; ++colIndex)
		{
			if (colIndex == pStartNode->mX && rowIndex == pStartNode->mY)
			{
				cout << "  S";
			}
			else if (colIndex == pGoalNode->mX && rowIndex == pGoalNode->mY)
			{
				cout << "  G";
			}
			else
			{
				cout << "  " << map[rowIndex][colIndex];
			}
		}

		cout << "\n   |\n";
	}
}

// Displays the nodes on a list.
void CSearchUtility::DisplayList(const string& listName, NodeList& nodeList)
{
	cout << "\n" << listName << ":";

	auto nextNode = nodeList.begin();
	auto lastNode = nodeList.end();

	while (nextNode != lastNode)
	{
		cout << "  " << (*nextNode)->mX << "," << (*nextNode)->mY;
		++nextNode;
	}
}

// Checks if the position for a node is valid.
bool CSearchUtility::CanCreateNode(TerrainMap& map, SMapSize& mapSize, int& posX, int& posY)
{
	// Check position NOT inside map area
	// and terrain at position is NOT wall.
	if (IsPositionInsideMapArea(mapSize, posX, posY) &&
		!IsPositionOnTerrainType(map, ETerrainCost::Wall, posX, posY))
	{
		return true;
	}

	return false;
}

// Checks if a position is inside the map area.
bool CSearchUtility::IsPositionInsideMapArea(SMapSize& mapSize, int& posX, int& posY)
{
	if (posX >= 0 && posX < mapSize.mWidth &&
		posY >= 0 && posY < mapSize.mHeight)
	{
		return true;
	}

	return false;
}

// Checks a terrain type at a position.
bool CSearchUtility::IsPositionOnTerrainType(TerrainMap& map, const ETerrainCost& terrainType,
	                                         int& posX, int& posY)
{
	if (map[posY][posX] == terrainType)
	{
		return true;
	}

	return false;
}

// Adds a node to the back of a list.
void CSearchUtility::AddNodeToListBack(NodeList& list, unique_ptr<SNode>& pNode)
{
	list.push_back(move(pNode));
}

// Adds a node to the front of a list.
void CSearchUtility::AddNodeToListFront(NodeList& list, unique_ptr<SNode>& pNode)
{
	list.push_front(move(pNode));
}

// Returns a node from the front of a list.
unique_ptr<SNode> CSearchUtility::RemoveNodeFromList(NodeList& list)
{
	unique_ptr<SNode> pNode = move(list.front());
	list.pop_front();

	return pNode;
}

// Checks if a node is in a list.
bool CSearchUtility::IsNodeInList(NodeList& nodeList, SNode* pNode)
{
	for (auto it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		if ((*it)->mX == pNode->mX && (*it)->mY == pNode->mY)
		{
			return true;
		}
	}

	return false;
}

// Checks if a node is at the goal.
bool CSearchUtility::IsCurrentNodeGoal(SNode* pCurrentNode, SNode* pGoalPos)
{
	if (pCurrentNode->mX == pGoalPos->mX &&
		pCurrentNode->mY == pGoalPos->mY)
	{
		return true;
	}

	return false;
}

// Creates a path to the goal using the last current node.
NodeList CSearchUtility::GetPathToGoal(SNode* pCurrentNode)
{
	// Node list path from start to goal position.
	NodeList path;

	// Create copy nodes from current node.
	unique_ptr<SNode> pCopyNode(new SNode);

	while (pCurrentNode != 0)
	{
		pCopyNode->mX = pCurrentNode->mX;
		pCopyNode->mY = pCurrentNode->mY;

		// Record current position on path (reverse order).
		path.push_front(move(pCopyNode));

		// Move onto next node in path.
		pCurrentNode = pCurrentNode->mpParent;

		pCopyNode.reset(new SNode);
	}

	return path;
}

// Checks if a node is in a list.
unique_ptr<SNode> CSearchUtility::GetNodeFromList(NodeList& nodeList, int& index)
{
	unique_ptr<SNode> node = move(nodeList.at(index));
	nodeList.erase(nodeList.begin() + index);

	return node;
}

// Returns the terrain cost of a position on the map.
int CSearchUtility::GetTerrainCost(TerrainMap& map, int& posX, int& posY)
{
	vector<ETerrainCost> row = map.at(posY);
	ETerrainCost tCost = row[posX];

	return tCost;
}

// Calculate the cost of the node.
int CSearchUtility::CalculateCost(TerrainMap& map, SNode* pNewNode, int& currentNodeCost)
{
	int tCost = GetTerrainCost(map, pNewNode->mX, pNewNode->mY);

	return (currentNodeCost + tCost);
}

// Calculates the heuristic value for the node.
int CSearchUtility::CalculateHeuristic(const SNode* pNewNode, const SNode* pGoalNode)
{
	int distX = abs(pGoalNode->mX - pNewNode->mX);
	int distY = abs(pGoalNode->mY - pNewNode->mY);

	return (distX + distY);
}

// Calculates a score value for the node.
int CSearchUtility::CalculateScore(SNode* pNewNode)
{
	return (pNewNode->mCost + pNewNode->mHeuristic);
}

// Check to see if a score from one nodes is less than the other.
bool CSearchUtility::CompareNodeScores(unique_ptr<SNode>& pNodeA, unique_ptr<SNode>& pNodeB)
{
	return pNodeA->mScore < pNodeB->mScore;
}

// Changes the order of the nodes on the open list based on the score.
void CSearchUtility::ReorderOpenList(NodeList& openList)
{
	sort(openList.begin(), openList.end(), CompareNodeScores);
}

// Checks if a node is in a list.
int CSearchUtility::GetNodeIndexFromList(NodeList& nodeList, SNode* pNode)
{
	for (auto it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		if ((*it)->mX == pNode->mX && (*it)->mY == pNode->mY)
		{
			return (it - nodeList.begin());
		}
	}

	return BAD_INDEX;  // Not in list.
}