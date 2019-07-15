
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: CMatrix4x4cut.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Defines and implements matrix functions for a model object.

**************************************************************************************************/

#ifndef _CMATRIX4X4_H
#define _CMATRIX4X4_H

class CMatrix4x4
{

// Concrete class - public access.
public:

	// Matrix elements.
	float e00, e01, e02, e03;
	float e10, e11, e12, e13;
	float e20, e21, e22, e23;
	float e30, e31, e32, e33;

	// Default constructor - leaves values uninitialised (for performance).
	CMatrix4x4() {}

	// Make this matrix the identity matrix.
	void CMatrix4x4::MakeIdentity()
	{
		e00 = 1.0f;
		e01 = 0.0f;
		e02 = 0.0f; 
		e03 = 0.0f;

		e10 = 0.0f;
		e11 = 1.0f;
		e12 = 0.0f;
		e13 = 0.0f;

		e20 = 0.0f;
		e21 = 0.0f;
		e22 = 1.0f;
		e23 = 0.0f;

		e30 = 0.0f;
		e31 = 0.0f;
		e32 = 0.0f;
		e33 = 1.0f;
	}

	// Set a single row (range 0-3) of the matrix using a CVector3. Fourth element left unchanged.
	void CMatrix4x4::SetRow( const int iRow, const CVector3& v )
	{
		float* pfElts = &e00 + iRow * 4;
		pfElts[0] = v.x;
		pfElts[1] = v.y;
		pfElts[2] = v.z;
	}
};

#endif  // _CMATRIX4X4_H