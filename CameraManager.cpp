
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: CameraManager.cpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Implements camera manager functions.

**************************************************************************************************/

#include "CameraManager.hpp"

// Constructor. Sets a new camera and the starting position. Saves the camera matrix.
CCameraManager::CCameraManager(ICamera* pCamera)
{
	mpCamera = pCamera;
	mpCamera->RotateLocalX(90.0f);
	mCamMode = ECamMode::Top;

	mpCamera->GetMatrix(mOriginalCamMatrix);
}

// Destructor.
CCameraManager::~CCameraManager() {}

// Moves the camera forward in the world.
void CCameraManager::MoveForward(float& updateTime)
{
	mpCamera->MoveZ(CAM_MOVE_SPEED * updateTime);
}

// Moves the camera backward in the world.
void CCameraManager::MoveBackward(float& updateTime)
{
	mpCamera->MoveZ(-CAM_MOVE_SPEED * updateTime);
}

// Moves the camera left in the world.
void CCameraManager::MoveLeft(float& updateTime)
{
	mpCamera->MoveX(-CAM_MOVE_SPEED * updateTime);
}

// Moves the camera right in the world.
void CCameraManager::MoveRight(float& updateTime)
{
	mpCamera->MoveX(CAM_MOVE_SPEED * updateTime);
}

// Updated the camera original position.
void CCameraManager::SetCameraStartPos(float x, float y, float z)
{
	ResetCameraPos();

	mpCamera->SetPosition(x, y, z);

	mpCamera->GetMatrix(mOriginalCamMatrix);
}

// Changes the position of the camera to the next camera mode.
void CCameraManager::ChangeCameraPos()
{
	if (mCamMode == ECamMode::Top)
	{
		mpCamera->RotateLocalX(CAM_ROT_POS_SIDE.x);
		mpCamera->MoveY(CAM_ROT_POS_SIDE.y);
		mpCamera->MoveZ(CAM_ROT_POS_SIDE.z);

		mCamMode = ECamMode::Side;
	}
	else if (mCamMode == ECamMode::Side)
	{
		mpCamera->RotateLocalX(CAM_ROT_POS_NEAR.x);
		mpCamera->MoveY(CAM_ROT_POS_NEAR.y);
		mpCamera->MoveZ(CAM_ROT_POS_NEAR.z);

		mCamMode = ECamMode::Near;
	}
	else if (mCamMode == ECamMode::Near)
	{
		mpCamera->RotateLocalX(CAM_ROT_POS_TOP.x);
		mpCamera->MoveY(CAM_ROT_POS_TOP.y);
		mpCamera->MoveZ(CAM_ROT_POS_TOP.z);

		mCamMode = ECamMode::Top;
	}
}

// Reset the camera position back to the original position.
void CCameraManager::ResetCameraPos()
{
	mpCamera->SetMatrix(mOriginalCamMatrix);
	mCamMode = ECamMode::Top;
}

// Gets the camera.
ICamera* CCameraManager::GetCamera()
{
	return mpCamera;
}