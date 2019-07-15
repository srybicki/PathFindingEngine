
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: Node.cpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Implements a node object presented on the map.

**************************************************************************************************/

#include "Node.hpp"

// Constructor. Creates a node model and sets the position.
// Sets the visible state to false.
CNode::CNode(IMesh* nodeMesh, const float& posX, const float& posY, const float& posZ)
{
	mpModel = nodeMesh->CreateModel(posX, posY, posZ);
	mVisible = false;
}

// Destructor.
CNode::~CNode() {}

// Returns the model of the node.
IModel* CNode::GetModel()
{
	return mpModel;
}

// Checks if the node is visible on the map.
bool CNode::IsVisible()
{
	if (mVisible)
	{
		return true;
	}

	return false;
}

// Moves the node position to show on the map. Sets the visible state to true.
void CNode::Show()
{
	mpModel->SetY(NODE_SHOW_POS_Y);
	mVisible = true;
}

// Moves the node position to hide from the map. Sets the visible state to false.
void CNode::Hide()
{
	mpModel->SetY(NODE_HIDE_POS_Y);
	mVisible = false;
}

// Sets the texture of the model.
void CNode::SetColour(const string& texName)
{
	mpModel->SetSkin(texName);
}

// Gets the local X position of the node.
float CNode::GetPosX()
{
	return mpModel->GetLocalX();
}

// Gets the local Y position of the node.
float CNode::GetPosY()
{
	return mpModel->GetLocalY();
}

// Gets the local Z position of the node.
float CNode::GetPosZ()
{
	return mpModel->GetLocalZ();
}