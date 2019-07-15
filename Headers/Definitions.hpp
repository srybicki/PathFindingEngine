
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: Definitions.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Defines different data types used in the map search. 

**************************************************************************************************/

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

// System include files.
#include <vector>
#include <deque>
#include <memory>

using namespace std;

// Used to identify if element not in list.
const int BAD_INDEX = -1;

// Represents a node in the search tree.
struct SNode
{
	int mX;               // x coordinate.
	int mY;               // y coordinate.
	int mCost;            // used in more complex algorithms.
	int mHeuristic;       // used in more complex algorithms.
	int mScore;           // used in more complex algorithms.
	SNode* mpParent = 0;  // note use of raw pointer here.
};

// Lists of nodes (e.g Open, Closed and Paths) are implemented as double-ended queues.
using NodeList = deque<unique_ptr<SNode>>;

// Terrain costs for map squares.
enum ETerrainCost
{
	Wall  = 0,
	Clear = 1,
	Water = 2,
	Wood  = 3
};

// Maps of any size are implemented as 2D vectors.
using TerrainMap = vector<vector<ETerrainCost>>;

// Holds the map width and height.
struct SMapSize
{
	int mWidth;
	int mHeight;
};

// Used in the smooth version of the path to the goal.
struct SPoint
{
	float mX, mY, mZ;
};

#endif  // _DEFINITIONS_H