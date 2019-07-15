
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: MathUtility.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Defines useful math functions for the tank.

**************************************************************************************************/

#ifndef _MATH_UTILITY_H
#define _MATH_UTILITY_H

// TL-Engine include file and namespace.
#include <TL-Engine.h>
using namespace tle;

// Custom include files.
#include "CVector3cut.hpp"
#include "CMatrix4x4cut.hpp"

class MathUtility
{

public:

	// Calculates the distance of a vector.
	// Param: Position XYZ.
	// Return: Distance value.
	static float DistanceVector(const CVector3& pos);

	// Makes an object turn and face another object.
	// Param: First model, Second model position XYZ, First model position XYZ.
	// Return:
	static void LookAt(IModel* modelA, CVector3 modelPosB, CVector3 modelPosA);

};

#endif  // _MATH_UTILITY_H