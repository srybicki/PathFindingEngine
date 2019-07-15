
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: SearchUtility.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Defines useful methods used by search algorithms.

**************************************************************************************************/

#ifndef _SEARCH_UTILITY_H
#define _SEARCH_UTILITY_H

// Custom include file.
#include "Definitions.hpp"

// System inlcude files.
#include <iostream>
#include <string>
#include <algorithm>

class CSearchUtility
{

public:

	// Displays the map and shows cost of each grid square.
	// Param: Map data, Map size, Start node, Goal node.
	// Return:
	static void DisplayMap(TerrainMap&, SMapSize&, SNode*, SNode*);

	// Displays the nodes on a list.
	// Param: List name, List of nodes.
	// Return:
	static void DisplayList(const string&, NodeList&);

	// Checks if the position for a node is valid.
	// Param: Map data, Map size, Node position X, Node position Y.
	// Return: True or False.
	static bool CanCreateNode(TerrainMap&, SMapSize&, int&, int&);

	// Checks if a position is inside the map area.
	// Param: Map size, Position X, Position Y.
	// Return: True or False.
	static bool IsPositionInsideMapArea(SMapSize&, int&, int&);

	// Checks a terrain type at a position.
	// Param: Map data, Terrain cost number, Position X, Position Y.
	// Return: True or False.
	static bool IsPositionOnTerrainType(TerrainMap&, const ETerrainCost&, int&, int&);

	// Adds a node to the back of a list.
	// Param: List of nodes, Node.
	// Return: Nothing.
	static void AddNodeToListBack(NodeList&, unique_ptr<SNode>&);

	// Adds a node to the front of a list.
	// Param: List of nodes, Node.
	// Return: Nothing.
	static void AddNodeToListFront(NodeList& list, unique_ptr<SNode>& pNode);

	// Removes a node from the front of a list.
	// Param: List of nodes.
	// Return: Node.
	static unique_ptr<SNode> RemoveNodeFromList(NodeList&);

	// Checks if a node is in a list.
	// Param: List of nodes, Node.
	// Return: True or False.
	static bool IsNodeInList(NodeList&, SNode*);

	// Checks if a node is at the goal.
	// Param: Current node, Goal node.
	// Return: True or False.
	static bool IsCurrentNodeGoal(SNode*, SNode*);

	// Creates a path to the goal using the last current node.
	// Param: Current node.
	// Return: List of nodes.
	static NodeList GetPathToGoal(SNode*);

	// Gets a node from a list based on index position.
	// Param: List of nodes, Node position index.
	// Return: Node.
	static unique_ptr<SNode> GetNodeFromList(NodeList&, int&);

	// Returns the terrain cost of a position on the map.
	// Param: Map data, Position X, Position Y
	// Return: Terrain cost number.
	static int GetTerrainCost(TerrainMap&, int&, int&);

	// Calculates the cost of the node.
	// Param: Map data, New node, Current node cost.
	// Return: Cost number.
	static int CalculateCost(TerrainMap&, SNode*, int&);

	// Calculates the heuristic value for the node.
	// Param: Current node, Goal node.
	// Return: Heuristic number.
	static int CalculateHeuristic(const SNode*, const SNode*);

	// Calculates the score of the node.
	// Param: New node.
	// Return: Cost number.
	static int CalculateScore(SNode*);

	// Checks to see if a score from one nodes is less than the other.
	// Param: First node, Second node.
	// Return: True or False.
	static bool CompareNodeScores(unique_ptr<SNode>&, unique_ptr<SNode>&);

	// Changes the order of the nodes on the open list based on the score.
	// Param: Open list nodes.
	// Return: Void.
	static void ReorderOpenList(NodeList&);

	// Gets the node position index in list.
	// Param: Open list nodes, Node.
	// Return: Index number or -1.
	static int GetNodeIndexFromList(NodeList&, SNode*);

};

#endif  // _SEARCH_UTILITY_H