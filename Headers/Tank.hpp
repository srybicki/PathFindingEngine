
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: Tank.hpp

	 Author: Simon Rybicki

	   Date: 01/02/19

	Version: 1.0

	   Info: Defines tank object.

**************************************************************************************************/

#ifndef _TANK_H
#define _TANK_H

// TL-Engine include file and namespace.
#include <TL-Engine.h>
using namespace tle;

// Custom inlcude files.
#include "Definitions.hpp"
#include "Node.hpp"
#include "MathUtility.hpp"

// System include files.
#include <vector>
#include <iostream>

// Mesh file name.
const string TANK_MESH = "Tank.x";

// Move speed of the tank.
const float TANK_SPEED = 5.0f;

// Hide position far away from camera view.
const CVector3 TANK_HIDE_POS = CVector3(-1000.0f, -1000.0f, -1000.0f);

// States of the tank.
enum ETankState
{
	Hide,
	Wait,
	Move,
	Done
};

class CTank
{

public:

	// Constructor. Creates the tank model and sets the initial position.
	// Param: TL mesh, Start position.
	// Return: Tank object.
	CTank(IMesh* tankMesh, const CVector3& position);

	// Destructor.
	// Param:
	// Return:
	~CTank();

	// Gets the tank mesh.
	// Param:
	// Return: TL mesh.
	IMesh* GetMesh();

	// Get the tank model.
	// Param:
	// Return: TL model.
	IModel* GetModel();

	// Set the path points for the tank to follow and updates the start position of the tank.
	// Param: Path points.
	// Return:
	void SetPathPoints(const vector<SPoint>& points);

	// Sets the starting position of the tank on the map.
	// Param: Start position XYZ.
	// Return:
	void SetStartPos(const CVector3& startPos);

	// Checks tank state is the expected state.
	// Param: State for tank.
	// Return: True or false.
	bool IsState(const ETankState& state);

	// Sets the tank state.
	// Param: State for tank.
	// Return:
	void SetState(const ETankState& state);

	// Checks the tank state. Moves the tank along the path to the goal.
	// Param: Latest update time.
	// Return:
	void Update(const float& updateTime);

	// Resets tank and path to initial state.
	// Param:
	// Return:
	void Reset();

	// Removes the tank model from the scene.
	// Param:
	// Return:
	void Remove();

private:

	IMesh* mpMesh;
	IModel* mpModel;
	float mOriginalMatrix[16];
	vector<SPoint> mPathPoints;
	int mTargetPointIndex;
	ETankState mState;

	// Updates the starting position of the tank to the first point on the path.
	// Param:
	// Return:
	void UpdateStartPosition();

	// Checks if the tank is at target point.
	// Param: Tank position.
	// Return:
	bool MovedToTargetPoint(const CVector3& tankPosition);

	// Sets the next target point for the tank, or the state to done.
	// Param: Tank position.
	// Return:
	void UpdateTargetPoint(const CVector3& tankPosition);
};

#endif  // _TANK_H