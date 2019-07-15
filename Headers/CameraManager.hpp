
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: CameraManager.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Defines the camera manager.

**************************************************************************************************/

#ifndef _CAMERA_MANAGER_H
#define _CAMERA_MANAGER_H

// TL-Engine include file and namespace.
#include <TL-Engine.h>
using namespace tle;

// Custom include files.
#include "CVector3cut.hpp"
#include "CMatrix4x4cut.hpp"

// Fixed camera type.
const ECameraType CAM_TYPE = kManual;

// Movement speed of the camera object.
const float CAM_MOVE_SPEED = 25.0f;

// Initial Y position in the world.
const float CAM_START_HEIGHT = 100.0f;

// Camera mode rotation (X) and positions (Y, Z) update values.
const CVector3 CAM_ROT_POS_TOP = CVector3(65.0f, 75.0f, 40.0f);
const CVector3 CAM_ROT_POS_SIDE = CVector3(-45.0f, -50.0f, -50.0f);
const CVector3 CAM_ROT_POS_NEAR = CVector3(-20.0f, -25.0f, 10.0f);

// Camera modes.
enum ECamMode
{
	Top,
	Side,
	Near
};

class CCameraManager
{

public:

	// Constructor. Sets a new camera and the starting position. Saves the camera matrix.
	// Param: TL Camera.
	// Return:
	CCameraManager(ICamera* pCamera);

	// Destructor.
	// Param:
	// Return:
	~CCameraManager();

	// Moves the camera forward in the world.
	// Param: Latest update time.
	// Return:
	void MoveForward(float& updateTime);

	// Moves the camera backward in the world.
	// Param: Latest update time.
	// Return:
	void MoveBackward(float& updateTime);

	// Moves the camera left in the world.
	// Param: Latest update time.
	// Return:
	void MoveLeft(float& updateTime);

	// Moves the camera right in the world.
	// Param: Latest update time.
	// Return:
	void MoveRight(float& updateTime);

	// Updated the camera original position.
	// Param: X Position, Y position, Z position.
	// Return:
	void SetCameraStartPos(float x, float y, float z);

	// Changes the position of the camera to the next camera mode.
	// Param:
	// Return:
	void ChangeCameraPos();

	// Reset the camera position back to the original position.
	// Param:
	// Return:
	void ResetCameraPos();

	// Gets the camera object.
	// Param:
	// Return: Camera.
	ICamera* GetCamera();

private:

	float mOriginalCamMatrix[16];
	ECamMode mCamMode;
	ICamera* mpCamera;

};

#endif  // _CAMERA_MANAGER_H