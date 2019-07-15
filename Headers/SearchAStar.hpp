
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: SearchAStar.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Definition for A* search algorithm.

**************************************************************************************************/

#ifndef _SEARCH_ASTAR_H
#define _SEARCH_ASTAR_H

#include "Definitions.hpp"
#include "Search.hpp"
#include "SearchUtility.hpp"

class CSearchAStar : public ISearch
{

public:

	// Constructor. Sets the name of the search.
	// Param: Search name.
	// Return: Search object.
	CSearchAStar(const string& name);

	// Destructor.
	// Param:
	// Return:
	~CSearchAStar();

	// Gets the name of the search.
	// Param:
	// Return: Search name.
	string GetName();

	// Searches for a path to the goal.
	// Param: Map, Map size, Goal node, Open list, Closed list, Path to goal, 
	//        Current round count, List sort count.
	// Return: True or false.
	bool FindPath(TerrainMap& map, SMapSize& mapSize, SNode* pGoalNode,
		          NodeList& openList, NodeList& closedList, NodeList& path, 
		          int& roundCount, int& sortCount);

private:

	string mName = "No Name";

	// Creates more nodes around the current node.
	// Param: Map, Map size, Current node, Goal node, Open list, Closed list, List sort count.
	// Return:
	void CreateNodes(TerrainMap& map, SMapSize& mapSize, unique_ptr<SNode>& pCurrentNode,
		             const SNode* pGoalNode, NodeList& openList, NodeList& closedList,
		             int& openListSortCount);

};

#endif  // _SEARCH_ASTAR_H