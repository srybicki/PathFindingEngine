
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: MathUtility.cpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Implements a useful math functions for the tank.

**************************************************************************************************/

#include "MathUtility.hpp"

// Calculates the distance of a vector.
float MathUtility::DistanceVector(const CVector3& pos)
{
	return sqrtf((pos.x * pos.x) + (pos.y * pos.y) + (pos.z * pos.z));
}

// Makes an object turn and face another object.
void MathUtility::LookAt(IModel* modelA, CVector3 modelPosB, CVector3 modelPosA)
{
	// Calculate matrix axes for model A.
	// Get facing (z) vector from positions.
	const CVector3 vecZ = Normalise(Subtract(modelPosB, modelPosA));

	// Use cross product to get other axes.
	// Normalise the axes.
	const CVector3 vecX = Normalise(Cross(kYAxis, vecZ));
	const CVector3 vecY = Normalise(Cross(vecZ, vecX));

	// Build matrix from axes + position.
	// Matrix constructor using four CVector3 vars.
	CMatrix4x4 modelANewMat;
	modelANewMat.MakeIdentity();
	modelANewMat.SetRow(0, vecX);
	modelANewMat.SetRow(1, vecY);
	modelANewMat.SetRow(2, vecZ);
	modelANewMat.SetRow(3, modelPosA);

	// Set the new position of model A using the new matrix.
	modelA->SetMatrix(&modelANewMat.e00);
}