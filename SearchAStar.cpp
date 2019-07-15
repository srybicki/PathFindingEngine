
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: SearchAStar.cpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Searches a map using A* search method.

**************************************************************************************************/

#include "SearchAStar.hpp"

// Constructor. Sets the name of the search.
CSearchAStar::CSearchAStar(const string& name)
{
	mName = name;
}

// Destructor.
CSearchAStar::~CSearchAStar()
{

}

// Returns the name of the search.
string CSearchAStar::GetName()
{
	return mName;
}

// Searches for a path to the goal.
bool CSearchAStar::FindPath(TerrainMap& map, SMapSize& mapSize, SNode* pGoalNode,
	                        NodeList& openList, NodeList& closedList, NodeList& path, 
	                        int& roundCount, int& sortCount)
{
	// Display next round number.
	cout << "\n ROUND " << (roundCount += 1) << "\n";

	// Take next node from the open list and make it current node.
	unique_ptr<SNode> pCurrentNode = CSearchUtility::RemoveNodeFromList(openList);

	// Check if current node is at goal.
	if (CSearchUtility::IsCurrentNodeGoal(pCurrentNode.get(), pGoalNode))
	{
		// Display both lists and current node.
		CSearchUtility::DisplayList(" Open List", openList);
		CSearchUtility::DisplayList(" Closed List", closedList);
		cout << "\n Current Node: " << pCurrentNode->mX << "," << pCurrentNode->mY << "\n";

		// Create path from start to goal.
		path = CSearchUtility::GetPathToGoal(pCurrentNode.get());

		// Display the open list sort count.
		cout << "\n Sort count: " << sortCount;

		return true;
	}

	// Generate new nodes around current node.
	CreateNodes(map, mapSize, pCurrentNode, pGoalNode, openList, closedList, sortCount);

	// Display both lists and current node.
	CSearchUtility::DisplayList(" Open List", openList);
	CSearchUtility::DisplayList(" Closed List", closedList);
	cout << "\n Current Node: " << pCurrentNode->mX << "," << pCurrentNode->mY << "\n";

	// Push current node onto closed list.
	CSearchUtility::AddNodeToListBack(closedList, pCurrentNode);
}

// Creates more nodes around the current node.
void CSearchAStar::CreateNodes(TerrainMap& map, SMapSize& mapSize, unique_ptr<SNode>& pCurrentNode,
	                           const SNode* pGoalNode, NodeList& openList, NodeList& closedList,
	                           int& openListSortCount)
{
	// Number and directions to expand from current node.
	const int totalExpansionNodes = 4;
	int expansionNodeDirections[totalExpansionNodes][2] =
	{
		{  0,  1 },  // north
		{  1,  0 },  // east 
		{  0, -1 },  // south
		{ -1,  0 }   // west
	};

	unique_ptr<SNode> pNewNode(new SNode);

	// Keep track of how many new nodes created.
	int newNodesCount = 0;

	// Make new nodes in order North, East, South, West.
	for (int i = 0; i < totalExpansionNodes; ++i)
	{
		// Set position of new node.
		pNewNode->mX = (pCurrentNode->mX + expansionNodeDirections[i][0]);
		pNewNode->mY = (pCurrentNode->mY + expansionNodeDirections[i][1]);

		// Check if new location for new node is valid.
		if (CSearchUtility::CanCreateNode(map, mapSize, pNewNode->mX, pNewNode->mY))
		{
			// Calculate cost for node cost.
			int newNodeCost = CSearchUtility::CalculateCost(map, pNewNode.get(), pCurrentNode->mCost);

			// Check new node is on open or closed list.
			int newNodeOpenListIndex = CSearchUtility::GetNodeIndexFromList(openList, pNewNode.get());
			int newNodeClosedListIndex = CSearchUtility::GetNodeIndexFromList(closedList, pNewNode.get());

			// Check if new node on any list 
			// and has equal or greater cost than current node.
			if ((newNodeOpenListIndex != BAD_INDEX || newNodeClosedListIndex != BAD_INDEX) &&
				newNodeCost >= pCurrentNode->mCost)
			{
				continue;
			}
			else
			{
				// Check if new node is on any list.
				if (newNodeOpenListIndex != BAD_INDEX)
				{
					pNewNode = move(CSearchUtility::GetNodeFromList(openList, newNodeOpenListIndex));
				}
				else if (newNodeClosedListIndex != BAD_INDEX)
				{
					pNewNode = move(CSearchUtility::GetNodeFromList(closedList, newNodeClosedListIndex));
				}

				// Set the parent of new node to current node.
				pNewNode->mpParent = pCurrentNode.get();

				// Set new node cost, heuristic and score.
				pNewNode->mCost = newNodeCost;
				pNewNode->mHeuristic = CSearchUtility::CalculateHeuristic(pNewNode.get(), pGoalNode);
				pNewNode->mScore = CSearchUtility::CalculateScore(pNewNode.get());

				// Put new node on open list.
				CSearchUtility::AddNodeToListBack(openList, pNewNode);
				newNodesCount += 1;
			}

			// Clear new node data for next new node.
			pNewNode.reset(new SNode);
		}
	}

	// Check if 1 or more new nodes were added to open list.
	if (newNodesCount != 0)
	{
		// Reorder open list nodes by score.
		CSearchUtility::ReorderOpenList(openList);
		openListSortCount += 1;
	}
}