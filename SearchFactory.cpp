
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: SearchFactory.cpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Implements new search function.

**************************************************************************************************/

#include "SearchBreadthFirst.hpp"
#include "SearchDepthFirst.hpp"
#include "SearchBestFirst.hpp"
#include "SearchDijkstras.hpp"
#include "SearchAStar.hpp"
#include "SearchFactory.hpp"

// Create new search object of the given type and return a pointer to it.
ISearch* NewSearch(ESearchType search)
{
	// Algorithm names.
	const string BREADTH_FIRST_NAME = "Breadth-First";
	const string DEPTH_FIRST_NAME = "Depth-First";
	const string BEST_FIRST_NAME = "Best-First";
	const string DIJKSTRAS_FIRST_NAME = "Dijkstra's";
	const string A_STAR_NAME = "A*";

	switch (search)
	{
	case BreadthFirst: return new CSearchBreadthFirst(BREADTH_FIRST_NAME);
	case DepthFirst: return new CSearchDepthFirst(DEPTH_FIRST_NAME);
	case BestFirst: return new CSearchBestFirst(BEST_FIRST_NAME);
	case Dijkstras: return new CSearchDijkstras(DIJKSTRAS_FIRST_NAME);
	case AStar: return new CSearchAStar(A_STAR_NAME);
	default: return 0;
	}
}
