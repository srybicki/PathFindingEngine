
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: SearchBreadthFirst.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Definition for Breadth-First search method.

**************************************************************************************************/

#ifndef _SEARCH_BREADTH_FIRST_H
#define _SEARCH_BREADTH_FIRST_H

#include "Definitions.hpp"
#include "Search.hpp" 
#include "SearchUtility.hpp"

class CSearchBreadthFirst : public ISearch
{

public:

	// Constructor. Sets the name of the search.
	// Param: Search name.
	// Return: Search object.
	CSearchBreadthFirst(const string& name);

	// Destructor.
	// Param:
	// Return:
	~CSearchBreadthFirst();

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
	// Param: Map, Map size, Current node, Goal node, Open list, Closed list.
	// Return:
	void CreateNodes(TerrainMap& map, SMapSize& mapSize, unique_ptr<SNode>& pCurrentNode,
		             NodeList& openList, NodeList& closedList);
};

#endif  // _SEARCH_BREADTH_FIRST_H