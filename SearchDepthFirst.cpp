
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: SearchBreadthFirst.cpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Searches a map using Depth-first search method.

**************************************************************************************************/

#include "SearchDepthFirst.hpp"

// Constructor. Sets the name of the search.
CSearchDepthFirst::CSearchDepthFirst(const string& name)
{
	mName = name;
}

// Destructor.
CSearchDepthFirst::~CSearchDepthFirst() {}

// Returns the name of the search.
string CSearchDepthFirst::GetName()
{
	return mName;
}

// Searches for a path to the goal.
bool CSearchDepthFirst::FindPath(TerrainMap& map, SMapSize& mapSize, SNode* pGoalNode,
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

		return true;
	}

	// Generate new nodes around current node.
	CreateNodes(map, mapSize, pCurrentNode, openList, closedList);

	// Display both lists and current node.
	CSearchUtility::DisplayList(" Open List", openList);
	CSearchUtility::DisplayList(" Closed List", closedList);
	cout << "\n Current Node: " << pCurrentNode->mX << "," << pCurrentNode->mY << "\n";

	// Push current node onto closed list.
	CSearchUtility::AddNodeToListFront(closedList, pCurrentNode);

	return false;  // No path found.
}

// Creates more nodes around the current node.
void CSearchDepthFirst::CreateNodes(TerrainMap& map, SMapSize& mapSize, unique_ptr<SNode>& pCurrentNode,
	                                NodeList& openList, NodeList& closedList)
{
	// Number and directions to expand from current node (reverse order).
	const int totalExpansionNodes = 4;
	int expansionNodeDirections[totalExpansionNodes][2] =
	{
		{ -1,  0 },  // west
		{  0, -1 },  // south
		{  1,  0 },  // east 
		{  0,  1 }   // north
	};

	// Setup a random order for creating each new node.
	int expandOrder[totalExpansionNodes] = { 0, 1, 2, 3 };
	srand(unsigned(time(0)));
	random_shuffle(begin(expandOrder), end(expandOrder));

	unique_ptr<SNode> pNewNode(new SNode);

	// Make new nodes in a random order.
	for (int i = 0; i < totalExpansionNodes; ++i)
	{
		// Set position of new node.
		pNewNode->mX = (pCurrentNode->mX + expansionNodeDirections[expandOrder[i]][0]);
		pNewNode->mY = (pCurrentNode->mY + expansionNodeDirections[expandOrder[i]][1]);

		// Check if node is NOT on open and closed list
		// and new location for new node is valid.
		if (!CSearchUtility::IsNodeInList(openList, pNewNode.get()) &&
			!CSearchUtility::IsNodeInList(closedList, pNewNode.get()) &&
			 CSearchUtility::CanCreateNode(map, mapSize, pNewNode->mX, pNewNode->mY))
		{
			// Set new node parent to current node.
			pNewNode->mpParent = pCurrentNode.get();

			// Put new node on open list.
			CSearchUtility::AddNodeToListFront(openList, pNewNode);

			// Clear new node data for next new node.
			pNewNode.reset(new SNode);
		}
	}
}