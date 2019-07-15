
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: Node.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Definition for node object.

**************************************************************************************************/

#ifndef _NODE_H
#define _NODE_H

// TL-Engine include file and namespace.
#include <TL-Engine.h>
using namespace tle;

// System include file.
#include <string>

// Nodes show and hide positions.
const float NODE_SHOW_POS_Y = 0.0f;
const float NODE_HIDE_POS_Y = -2.5f;

// The size of the collision body around a node.
const float NODE_COLLISION_SPHERE_RADIUS = 0.1f;

// Node mesh file name.
const string NODE_MESH = "Node.x";

// Node texture file names.
const string NODE_BLUE_TEX = "BlueNode.png";
const string NODE_RED_TEX = "RedNode.png";

class CNode
{

public:

	// Constructor. Creates a node model and sets the position.
    // Sets the visible state to false.
	// Param: Node mesh, X position, Y position, Z position.
	// Return: Node object.
	CNode(IMesh* nodeMesh, const float& posX, const float& posY, const float& posZ);

	// Destructor.
	// Param:
	// Return:
	~CNode();

	// Returns the model of the node.
	// Param:
	// Return: Node model.
	IModel* GetModel();

	// Checks if the node is visible on the map.
	// Param:
	// Return: True or false.
	bool IsVisible();

	// Moves the node position to show on the map. Sets the visible state to true.
	// Param:
	// Return:
	void Show();

	// Moves the node position to hide from the map. Sets the visible state to false.
	// Param:
	// Return:
	void Hide();

	// Sets the texture of the model.
	// Param: Texture name.
	// Return:
	void SetColour(const string& texName);

	// Gets the local X position of the node.
	// Param:
	// Return: X position.
	float GetPosX();

	// Gets the local Y position of the node.
	// Param:
	// Return: Y position.
	float GetPosY();

	// Gets the local Z position of the node.
	// Param:
	// Return: Z position.
	float GetPosZ();

private:

	bool mVisible;
	IModel* mpModel;

};

#endif  // _NODE_H