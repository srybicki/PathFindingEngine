
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: SkyBox.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Defines a sky box object.

**************************************************************************************************/

// TL-Engine include file and namespace.
#include <TL-Engine.h>
using namespace tle;

// Sky box mesh file name.
const string SKY_MESH = "SkyBox.x";

class CSkybox
{

public:

	// Constructor. Sets the skybox mesh and creates the model.
	// Param: Sky box mesh.
	// Return: Sky box object.
	CSkybox(IMesh* skyboxMesh);

	// Destructor.
	// Param:
	// Return:
	~CSkybox();

	// Sets the position of the sky box object.
	// Param: X position, Y position, Z position.
	// Return:
	void SetPosition(const float& x, const float& y, const float& z);

	// Removes the sky box model from the scene.
	// Param:
	// Return:
	void RemoveModel();

	// Gets the sky box mesh.
	// Param:
	// Return: Sky box mesh.
	IMesh* GetMesh();

private:

	IMesh* mpMesh;
	IModel* mpModel;

};
