
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: Search.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: ISearch interface class - cannot be instantiated.

**************************************************************************************************/

#ifndef _SEARCH_H
#define _SEARCH_H

#include "Definitions.hpp"

class ISearch
{

public:

	// Destructor.
	virtual ~ISearch() {}

	// Returns the name of the search.
	virtual string GetName() = 0;

	// Searches for a path from the start to the goal.
	virtual bool FindPath(TerrainMap& map, SMapSize& mapSize, SNode* pGoalNode,
						  NodeList& openList, NodeList& closedList, NodeList& path, 
		                  int& roundCount, int& sortCount) = 0;
};

#endif  // _SEARCH_H