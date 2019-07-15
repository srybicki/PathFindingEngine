
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: SkyBox.cpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Implements a sky box object.

**************************************************************************************************/

#include "SkyBox.hpp";

// Constructor. Sets the skybox mesh and creates the model.
CSkybox::CSkybox(IMesh* skyboxMesh)
{
	mpMesh = skyboxMesh;
	mpModel = mpMesh->CreateModel();
}

// Destructor.
CSkybox::~CSkybox() {}

// Sets the position of the sky box object.
void CSkybox::SetPosition(const float& x, const float& y, const float& z)
{
	mpModel->SetPosition(x, y, z);
}

// Removes the sky box model from the scene.
void CSkybox::RemoveModel()
{
	if (mpMesh != nullptr)
	{
		mpMesh->RemoveModel(mpModel);
	}
}

// Gets the sky box mesh.
IMesh* CSkybox::GetMesh()
{
	return mpMesh;
}