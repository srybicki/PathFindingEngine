
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: Tank.cpp

	 Author: Simon Rybicki

	   Date: 01/02/19

	Version: 1.0

	   Info: Implements tank object.

**************************************************************************************************/

#include "Tank.hpp"

// Constructor. Creates the tank model and sets the initial position.
CTank::CTank(IMesh* tankMesh, const CVector3& position)
{
	mpMesh = tankMesh;
	mpModel = mpMesh->CreateModel(position.x, position.y, position.z);
	mpModel->GetMatrix(mOriginalMatrix);

	mState = ETankState::Hide;
	mTargetPointIndex = 0;
}

// Destructor.
CTank::~CTank() {}

// Gets the tank mesh.
IMesh* CTank::GetMesh()
{
	return mpMesh;
}

// Gets the tank model.
IModel* CTank::GetModel()
{
	return mpModel;
}

// Set the path points for the tank to follow and updates the start position of the tank.
void CTank::SetPathPoints(const vector<SPoint>& points)
{
	mPathPoints = points;

	UpdateStartPosition();
}

// Sets the starting position of the tank on the map.
void CTank::SetStartPos(const CVector3& startPos)
{
	mpModel->SetPosition(startPos.x, startPos.y, startPos.z);
}

// Checks tank state is the expected state.
bool CTank::IsState(const ETankState& state)
{
	if (state == mState)
	{
		return true;
	}

	return false;
}

// Sets the tank state.
void CTank::SetState(const ETankState& state)
{
	mState = state;
}

// Checks the tank state. Moves the tank along the path to the goal.
void CTank::Update(const float& frameTime)
{
	if (mState == ETankState::Move)
	{
		// Get tank position.
		const CVector3 tankPosition = CVector3(mpModel->GetLocalX(),
			mpModel->GetLocalY(),
			mpModel->GetLocalZ());

		// Check if tank is NOT at target node.
		if (!MovedToTargetPoint(tankPosition))
		{
			// Move guard towards patrol point.
			mpModel->MoveLocalZ(TANK_SPEED * frameTime);
		}
		else
		{
			UpdateTargetPoint(tankPosition);
		}
	}
}

// Resets tank and path to initial state.
void CTank::Reset()
{
	mpModel->SetMatrix(mOriginalMatrix);
	mState = ETankState::Hide;
	mPathPoints.clear();
	mTargetPointIndex = 0;
}

// Removes the tank model from the scene.
void CTank::Remove()
{
	if (mpMesh != 0)
	{
		mpMesh->RemoveModel(mpModel);
	}
}

// Updates the starting position of the tank to the first point on the path.
void CTank::UpdateStartPosition()
{
	if (mPathPoints.size() != 0)
	{
		CVector3 startPos = CVector3(mPathPoints[0].mX,
			mPathPoints[0].mY,
			mPathPoints[0].mZ);

		// Set tank to start location.
		SetStartPos(startPos);

		// Get tank to face next node.
		UpdateTargetPoint(startPos);
	}
}

// Checks if the tank is at target point.
bool CTank::MovedToTargetPoint(const CVector3& tankPosition)
{
	// Get target point position.
	const CVector3 targetPointPosition = CVector3(mPathPoints[mTargetPointIndex].mX,
		mPathPoints[mTargetPointIndex].mY,
		mPathPoints[mTargetPointIndex].mZ);

	// Get vector between tank and target point.
	const CVector3 vecToTargetPoint = Subtract(targetPointPosition, tankPosition);

	// Get distance between tank and target point.
	const float collisionDistance = MathUtility::DistanceVector(vecToTargetPoint);

	// Check if tank has collided with target point.
	if (collisionDistance < NODE_COLLISION_SPHERE_RADIUS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Sets the next target point for the tank, or the state to done.
void CTank::UpdateTargetPoint(const CVector3& tankPosition)
{
	// Check if current target node is the last node.
	if ((mTargetPointIndex + 1) < mPathPoints.size())
	{
		mTargetPointIndex += 1;

		// TEMP - REMOVE
		//cout << "\n target index: " << mTargetPointIndex;

		// Get target point position.
		const CVector3 targetPointPosition = CVector3(mPathPoints[mTargetPointIndex].mX,
			mPathPoints[mTargetPointIndex].mY,
			mPathPoints[mTargetPointIndex].mZ);

		// Turn tank to face the next target point.
		MathUtility::LookAt(mpModel, targetPointPosition, tankPosition);
	}
	else
	{
		mState = ETankState::Done;
	}
}