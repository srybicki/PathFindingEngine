
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: SearchFactory.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Defines search types and new search function.

**************************************************************************************************/

#ifndef _SEARCH_FACTORY_H
#define _SEARCH_FACTORY_H

#include "Search.hpp"  // Search interface class.

// List of implemented search algorithms.
enum ESearchType
{
	BreadthFirst,
	DepthFirst,
	BestFirst,
	Dijkstras,
	AStar
};

// Factory function to create CSearchXXX object where XXX is the given search type.
// Param: Search type.
// Return: Search object.
ISearch* NewSearch(ESearchType search);

#endif  // _SEARCH_FACTORY_H