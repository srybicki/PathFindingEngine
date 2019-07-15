
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: PathFinding.cpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Entry point of the program.
	         Initialises the TL engine and objects in the scene.
			 Sets controls for a search to be carried out.

**************************************************************************************************/

// TL-Engine include file and namespace.
#include <TL-Engine.h>	
using namespace tle;

// Custom include files.
#include "Search.hpp"
#include "SearchFactory.hpp"
#include "Definitions.hpp"
#include "SearchUtility.hpp"
#include "CVector3cut.hpp"
#include "CMatrix4x4cut.hpp"
#include "CameraManager.hpp"
#include "Button.hpp"
#include "MapData.hpp"
#include "MapView.hpp"
#include "Tank.hpp"
#include "SkyBox.hpp"

// System include file.
#include <sstream>

// Name of folder in project than stores models and textures.
const string ASSET_FOLDER_NAME = "Media";

// HUB background texture file name.
const string HUD_BACKGROUND_TEX = "HudBackground.png";

// HUD text font type and size.
const string FONT_TYPE = "Arial";
const int FONT_SIZE = 26;

// Algorithm name text x and y positions, and colour.
const int ALGORITHM_TEXT_POS_X = 45;
const int ALGORITHM_TEXT_POS_Y = 15;
const unsigned int ALGORITHM_TEXT_COLOUR = kBlack;

// Error text x and y positions, colour, and message.
const int ERROR_TEXT_POS_X = 640;
const int ERROR_TEXT_POS_Y = 15;
const unsigned int ERROR_TEXT_COLOUR = kRed;
const string ERROR_TEXT_MESSAGE = "Error: See console window.";

// Fixed update and max frame times.
const float FIXED_UPDATE_FRAME_TIME = (1.0f / 60.0f);
const float MAX_FIXED_FRAME_TIME_X1 = 10.0f;
const float MAX_FIXED_FRAME_TIME_X2 = 5.0f;

// States of the search.
enum ESearchState
{
	Stopped,
	Playing,
	Paused,
	Finished
};

// Scene objects.
I3DEngine* gpEngine;
ISprite* gpHudBackground;
ISprite* gpTextBox;
IFont* gpFont;

// Define scene state.
ESearchState gSearchState;

// Camera manager for a TL camera.
CCameraManager* gpCamera;

// Buttons on top bar.
CButton* gpLeftSelectButton;
CButton* gpRightSelectButton;
CButton* gpLoadMapButton;
CButton* gpLoadCoordsButton;
CButton* gpPlayButton;
CButton* gpPauseButton;
CButton* gpStopButton;
CButton* gpStepButton;
CButton* gpFastForwardButton;

// Create path search methods.
const int TOTAL_SEARCH_METHODS = 5;
ISearch* gpSearchMethods[TOTAL_SEARCH_METHODS] = { 
	NewSearch(BreadthFirst),
	NewSearch(DepthFirst),
	NewSearch(BestFirst),
	NewSearch(Dijkstras),
	NewSearch(AStar) 
};

// Index of search method selected.
int gSearchMethodIndex;

// Name of search method selected.
string gSearchMethodName;

// Map and coords data manager.
CMapData* gpMapData;

// Map and coords view manager;
CMapView* gpMapView;

// Tank object to follow the path to goal.
CTank* gpTank;

// Sky box object surrounding map.
CSkybox* gpSkyBox;

// Keep track of search status.
bool gSearchActive = false;

// Keep a count of number of searches done.
int gSearchCount = 0;

// Keep a count of the sort done on the open list (A* search).
int gSearchListSortCount = 0;

// Set error flag initial state;
bool gErrorFlag = false;

// Set initial max frame time.
float gMaxFixedFrameTime = MAX_FIXED_FRAME_TIME_X1;

// Keep track of frame time.
float gFixedFrameTimeCount = 0.0f;

// Start, Update and End parts of the 3D scene.
void SceneStart();
void SceneUpdate();
void SceneEnd();

// Update functions.
void UpdateCamera(float& frameTime);
void UpdateText();
void UpdateSearch(float& frameTime, float& fixedFrameTime);

// Search functions.
void SearchStop(float& frameTime, int& mouseX, int& mouseY);
void SearchPlay(float& frameTime, float& fixedFrameTime, int& mouseX, int& mouseY);
void SearchPause(float& frameTime, int& mouseX, int& mouseY);
void SearchFinish(float& frameTime, int& mouseX, int& mouseY);

// Helper functions.
void SetErrorFlag();
void ClearErrorFlag();
void PreviousSearchMethod();
void NextSearchMethod();

void main()
{
	SceneStart();

	// The main game loop, repeat until engine is stopped.
	while (gpEngine->IsRunning())
	{
		// Draw the scene.
		gpEngine->DrawScene();

		// Update the scene.
		SceneUpdate();

		// Check if the exit program key has been pressed.
		if (gpEngine->KeyHit(Key_Escape))
		{
			gpEngine->Stop();
		}
	}

	SceneEnd();

	// Delete the 3D engine now we are finished with it.
	gpEngine->Delete();
}

// Initilises objects used in the scene and assigns default values.
void SceneStart()
{
	// Create a 3D engine (using TLX engine here) and open a window for it.
	gpEngine = New3DEngine(kTLX);
	gpEngine->StartWindowed();

	// Add default folder for meshes and other media.
	gpEngine->AddMediaFolder(ASSET_FOLDER_NAME);

	// Create a new camera for the scene.
	gpCamera = new CCameraManager(gpEngine->CreateCamera(CAM_TYPE, 0.0f, CAM_START_HEIGHT, 0.0f));

	// Create sky box object.
	gpSkyBox = new CSkybox(gpEngine->LoadMesh(SKY_MESH));

	// Load HUD background sprite.
	gpHudBackground = gpEngine->CreateSprite(HUD_BACKGROUND_TEX, 0.0f, 0.0f);
	gpHudBackground->SetZ(HUD_POS_Z);

	// Load HUD button and text box sprites (left side).
	float leftHudPosX = 0.0f;
	gpLeftSelectButton = new CButton(gpEngine->CreateSprite(LEFT_SELECT_BUTTON_TEX, leftHudPosX, 0.0f), 
		                             EButtonState::Enabled, SELECT_BUTTON_WIDTH, BUTTON_SIZE);
	leftHudPosX += (SELECT_BUTTON_WIDTH + BUTTON_SPACER);
	gpTextBox = gpEngine->CreateSprite(TEXT_BOX_TEX, leftHudPosX, 0.0f, TEXT_BOX_POS_Z);
	leftHudPosX += (TEXT_BOX_WIDTH + BUTTON_SPACER);
	gpRightSelectButton = new CButton(gpEngine->CreateSprite(RIGHT_SELECT_BUTTON_TEX, leftHudPosX, 0.0f), 
									  EButtonState::Enabled, SELECT_BUTTON_WIDTH, BUTTON_SIZE);

	// Load HUD button sprites (right side).
	float rightHudPosX = (gpEngine->GetWidth() - BUTTON_SIZE);
	gpFastForwardButton = new CButton(gpEngine->CreateSprite(FAST_FORWARD_BUTTON_TEX, rightHudPosX, 0.0f), 
		                              EButtonState::Disabled, BUTTON_SIZE, BUTTON_SIZE);
	rightHudPosX -= BUTTON_SIZE;
	gpStepButton = new CButton(gpEngine->CreateSprite(STEP_BUTTON_TEX, rightHudPosX, 0.0f), 
		                       EButtonState::Disabled, BUTTON_SIZE, BUTTON_SIZE);
	rightHudPosX -= BUTTON_SIZE;
	gpStopButton = new CButton(gpEngine->CreateSprite(STOP_BUTTON_TEX, rightHudPosX, 0.0f), 
		                       EButtonState::Disabled, BUTTON_SIZE, BUTTON_SIZE);
	rightHudPosX -= BUTTON_SIZE;
	gpPauseButton = new CButton(gpEngine->CreateSprite(PAUSE_BUTTON_TEX, rightHudPosX, 0.0f), 
		                        EButtonState::Disabled, BUTTON_SIZE, BUTTON_SIZE);
	rightHudPosX -= BUTTON_SIZE;
	gpPlayButton = new CButton(gpEngine->CreateSprite(PLAY_BUTTON_TEX, rightHudPosX, 0.0f), 
		                       EButtonState::Enabled, BUTTON_SIZE, BUTTON_SIZE);
	rightHudPosX -= BUTTON_SIZE;
	gpLoadCoordsButton = new CButton(gpEngine->CreateSprite(COORDS_BUTTON_TEX, rightHudPosX, 0.0f), 
		                             EButtonState::Enabled, BUTTON_SIZE, BUTTON_SIZE);
	rightHudPosX -= BUTTON_SIZE;
	gpLoadMapButton = new CButton(gpEngine->CreateSprite(MAP_BUTTON_TEX, rightHudPosX, 0.0f), 
		                          EButtonState::Enabled, BUTTON_SIZE, BUTTON_SIZE);

	// Load font type.
	gpFont = gpEngine->LoadFont(FONT_TYPE, FONT_SIZE);

	// Set inital search method index and name.
	gSearchMethodIndex = 0;
	gSearchMethodName = gpSearchMethods[gSearchMethodIndex]->GetName();

	// Create a tank.
	gpTank = new CTank(gpEngine->LoadMesh(TANK_MESH), TANK_HIDE_POS);

	// Initialise map data manager.
	gpMapData = new CMapData();

	// Initialise map view meshes.
	IMesh* mapMeshCollection[TOTAL_GRID_MESHES] = { gpEngine->LoadMesh(WALL_MESH), 
		                                            gpEngine->LoadMesh(CLEAR_MESH), 
		                                            gpEngine->LoadMesh(WATER_MESH),
		                                            gpEngine->LoadMesh(WOOD_MESH) };
	IMesh* startMesh = gpEngine->LoadMesh(START_MESH);
	IMesh* goalMesh = gpEngine->LoadMesh(GOAL_MESH);
	IMesh* earthMesh = gpEngine->LoadMesh(EARTH_MESH);
	IMesh* nodeMesh = gpEngine->LoadMesh(NODE_MESH);

	// Initialise map view manager.
	gpMapView = new CMapView(mapMeshCollection, startMesh, goalMesh, earthMesh, nodeMesh);

	// Set the inital state of the game.
	gSearchState = ESearchState::Stopped;

	// Start the frame timer.
	gpEngine->Timer();
}

// Updates objects in the scene.
void SceneUpdate()
{
	// Get the next frame time.
	float frameTime = gpEngine->Timer();
	float fixedFrameTime = (1.0f / (1.0f / FIXED_UPDATE_FRAME_TIME));

	UpdateCamera(frameTime);

	UpdateText();

	UpdateSearch(frameTime, fixedFrameTime);
}

// Unloads objects from the scene and cleans memory.
void SceneEnd()
{
	gpEngine->RemoveCamera(gpCamera->GetCamera());
	gpEngine->RemoveFont(gpFont);
	gpEngine->RemoveSprite(gpLeftSelectButton->GetSprite());
	gpEngine->RemoveSprite(gpTextBox);
	gpEngine->RemoveSprite(gpRightSelectButton->GetSprite());
	gpEngine->RemoveSprite(gpLoadMapButton->GetSprite());
	gpEngine->RemoveSprite(gpLoadCoordsButton->GetSprite());
	gpEngine->RemoveSprite(gpPlayButton->GetSprite());
	gpEngine->RemoveSprite(gpPauseButton->GetSprite());
	gpEngine->RemoveSprite(gpStopButton->GetSprite());
	gpEngine->RemoveSprite(gpStepButton->GetSprite());
	gpEngine->RemoveSprite(gpFastForwardButton->GetSprite());
	gpEngine->RemoveSprite(gpHudBackground);

	gpTank->Remove();

	if (gpMapData->IsMapDataLoaded())
	{
		if (gpMapData->IsCoordsDataLoaded())
		{
			gpMapView->DestroyCoords(gpMapData->GetMap(), gpMapData->GetStartNode(), gpMapData->GetGoalNode());
		}

		gpMapView->DestroyMap(gpMapData->GetMap(), gpMapData->GetMapSize(),
			                  gpMapData->GetStartNode(), gpMapData->GetGoalNode());
	}

	gpSkyBox->RemoveModel();
	gpEngine->RemoveMesh(gpSkyBox->GetMesh());
	gpEngine->RemoveMesh(gpTank->GetMesh());
	gpEngine->RemoveMesh(gpMapView->GetStartMesh());
	gpEngine->RemoveMesh(gpMapView->GetGoalMesh());
	gpEngine->RemoveMesh(gpMapView->GetNodeMesh());
	for (int i = 0; i < TOTAL_GRID_MESHES; ++i)
	{
		gpEngine->RemoveMesh(gpMapView->GetMapMesh(i));
	}
	
	delete gpCamera;
	delete gpLeftSelectButton;
	delete gpRightSelectButton;
	delete gpLoadMapButton;
	delete gpLoadCoordsButton;
	delete gpPlayButton;
	delete gpPauseButton;
	delete gpStopButton;
	delete gpStepButton;
	delete gpFastForwardButton;
	delete gpMapData;
	delete gpMapView;
	delete gpTank;
	delete gpSkyBox;

	for (int i = 0; i < TOTAL_SEARCH_METHODS; ++i)
	{
		delete gpSearchMethods[i];
	}	
}

// Updates the Camera position and angle.
void UpdateCamera(float& frameTime)
{
	// Check zoom key press.
	if (gpEngine->KeyHit(Key_1))
	{
		gpCamera->ChangeCameraPos();
	}
	else if (gpEngine->KeyHit(Key_0))
	{
		gpCamera->ResetCameraPos();
	}

	// Check move key press up/down.
	if (gpEngine->KeyHeld(Key_Up))
	{
		gpCamera->MoveForward(frameTime);
	}
	else if (gpEngine->KeyHeld(Key_Down))
	{
		gpCamera->MoveBackward(frameTime);
	}

	// Check move key press left/right.
	if (gpEngine->KeyHeld(Key_Left))
	{
		gpCamera->MoveLeft(frameTime);
	}
	else if (gpEngine->KeyHeld(Key_Right))
	{
		gpCamera->MoveRight(frameTime);
	}
}

// Updates the text in the HUD.
void UpdateText()
{
	// Display the current algorithm selected.
	stringstream outText;
	outText << gSearchMethodName;
	gpFont->Draw(outText.str(), ALGORITHM_TEXT_POS_X, ALGORITHM_TEXT_POS_Y, ALGORITHM_TEXT_COLOUR);
	outText.str("");

	// Check if an error has occured.
	if (gErrorFlag)
	{
		outText << ERROR_TEXT_MESSAGE;
		gpFont->Draw(outText.str(), ERROR_TEXT_POS_X, ERROR_TEXT_POS_Y, ERROR_TEXT_COLOUR, EHorizAlignment::kCentre);
		outText.str("");
	}
}

// Updates the search to the goal.
void UpdateSearch(float& frameTime, float& fixedFrameTime)
{
	int mousePosX = -1;
	int mousePosY = -1;

	if (gpEngine->KeyHit(EKeyCode::Mouse_LButton))
	{
		mousePosX = gpEngine->GetMouseX();
		mousePosY = gpEngine->GetMouseY();
	}

	switch (gSearchState)
	{
	case ESearchState::Stopped: 
		SearchStop(frameTime, mousePosX, mousePosY);
		break;
	case ESearchState::Playing:
		SearchPlay(frameTime, fixedFrameTime, mousePosX, mousePosY);
		break;
	case ESearchState::Paused:
		SearchPause(frameTime, mousePosX, mousePosY);
		break;
	case ESearchState::Finished:
		SearchFinish(frameTime, mousePosX, mousePosY);
		break;
	}
}

void SearchStop(float& frameTime, int& mouseX, int& mouseY)
{
	if (gpLeftSelectButton->IsActive() && gpLeftSelectButton->Clicked(mouseX, mouseY))
	{
		PreviousSearchMethod();
	}
	else if (gpRightSelectButton->IsActive() && gpRightSelectButton->Clicked(mouseX, mouseY))
	{
		NextSearchMethod();
	}
	else if (gpLoadMapButton->IsActive() && gpLoadMapButton->Clicked(mouseX, mouseY))
	{
		gpLoadMapButton->SetState(EButtonState::Disabled);

		if (gpMapData->IsMapDataLoaded())
		{
			if (gpTank->IsState(ETankState::Wait))
			{
				// Hide the tank before the search.
				gpTank->Reset();
			}

			if (gpMapData->IsCoordsDataLoaded())
			{
				gpMapView->DestroyCoords(gpMapData->GetMap(), gpMapData->GetStartNode(), gpMapData->GetGoalNode());
			}

			gpMapView->DestroyMap(gpMapData->GetMap(), gpMapData->GetMapSize(),
				                  gpMapData->GetStartNode(), gpMapData->GetGoalNode());
			gpMapView->ClearData();
			gpMapData->ClearData();
		}

		bool mapLoaded = gpMapData->LoadMapData();

		if (mapLoaded)
		{
			cout << "\n Loaded map data.";
			ClearErrorFlag();

			gpMapView->CreateMap(gpMapData->GetMap(), gpMapData->GetMapSize());

			float midX = gpMapView->GetMapMidX();
			float midZ = gpMapView->GetMapMidZ();

			gpSkyBox->SetPosition(midX, 0.0f, midZ);
			gpCamera->SetCameraStartPos(midX, CAM_START_HEIGHT, midZ);
		}
		else
		{
			SetErrorFlag();
		}

		gpLoadMapButton->SetState(EButtonState::Enabled);
	}
	else if (gpLoadCoordsButton->IsActive() && gpLoadCoordsButton->Clicked(mouseX, mouseY))
	{
		gpLoadCoordsButton->SetState(EButtonState::Disabled);

		if (!gpMapData->IsMapDataLoaded())
		{
			cout << "\n Map has not been loaded.";
			SetErrorFlag();
		}
		else
		{
			if (gpTank->IsState(ETankState::Wait))
			{
				// Hide the tank before the search.
				gpTank->Reset();

				// Reset nodes.
				gpMapView->ResetListNodes();
				gpMapData->ResetLists();
			}

			if (gpMapData->IsCoordsDataLoaded())
			{
				gpMapView->DestroyCoords(gpMapData->GetMap(), gpMapData->GetStartNode(), gpMapData->GetGoalNode());
			}

			bool coordsLoaded = gpMapData->LoadCoordsData();

			if (coordsLoaded)
			{
				cout << "\n Loaded coords data.";
				ClearErrorFlag();

				gpMapView->CreateCoords(gpMapData->GetMap(), gpMapData->GetStartNode(), gpMapData->GetGoalNode());
			}
			else
			{
				SetErrorFlag();
			}
		}

		gpLoadCoordsButton->SetState(EButtonState::Enabled);
	}
	else if (gpPlayButton->IsActive() && gpPlayButton->Clicked(mouseX, mouseY))
	{
		if (!gpMapData->IsMapDataLoaded())
		{
			cout << "\n Map has not been loaded.";
			SetErrorFlag();
		}
		else if (!gpMapData->IsCoordsDataLoaded())
		{
			cout << "\n Coords have not been loaded.";
			SetErrorFlag();
		}
		else
		{
			ClearErrorFlag();

			gpLeftSelectButton->SetState(EButtonState::Disabled);
			gpRightSelectButton->SetState(EButtonState::Disabled);
			gpLoadMapButton->SetState(EButtonState::Disabled);
			gpLoadCoordsButton->SetState(EButtonState::Disabled);
			gpPlayButton->SetState(EButtonState::Disabled);

			if (!gSearchActive)
			{
				// Check if tank completed previous search.
				if(gpTank->IsState(ETankState::Wait))
				{
					// Hide the tank before the search.
					gpTank->Reset();

					// Reset nodes.
					gpMapView->ResetListNodes();
					gpMapData->ResetLists();
				}

				// Reset search and sort counts.
				gSearchCount = 0;
				gSearchListSortCount = 0;

				// Setup the first node.
				SNode* pStartNode = gpMapData->GetStartNode();
				SNode* pGoalNode = gpMapData->GetStartNode();
				unique_ptr<SNode> pTempNode(new SNode);

				// Set position.
				pTempNode->mX = pStartNode->mX;
				pTempNode->mY = pStartNode->mY;

				// Calculate start node cost, heuristic and score values.
				pTempNode->mCost = 0;
				pTempNode->mHeuristic = CSearchUtility::CalculateHeuristic(pTempNode.get(), pGoalNode);
				pTempNode->mScore = CSearchUtility::CalculateScore(pTempNode.get());

				// Add the first node to the open list.
				CSearchUtility::AddNodeToListBack(gpMapData->GetOpenList(), pTempNode);

				// Update map node lists.
				gpMapView->UpdateMapNodes(gpMapView->GetOpenListMapNodes(), gpMapData->GetOpenList());

				// Show new nodes on map.
				gpMapView->ShowNodes(gpMapView->GetOpenListMapNodes());

				// Update current node position.
				gpMapData->UpdateCurrentNode();

				// Show current node on map.
				gpMapView->ShowCurrentNode(gpMapData->GetCurrentNode());

				gFixedFrameTimeCount = 0.0f;

				// Set search speed (x1).
				gMaxFixedFrameTime = MAX_FIXED_FRAME_TIME_X1;

				gSearchActive = true;
			}

			gpPauseButton->SetState(EButtonState::Enabled);
			gpStopButton->SetState(EButtonState::Enabled);
			gpFastForwardButton->SetState(EButtonState::Enabled);

			gSearchState = ESearchState::Playing;
		}
	}
}

void SearchPlay(float& frameTime, float& fixedFrameTime, int& mouseX, int& mouseY)
{
	gFixedFrameTimeCount += fixedFrameTime;

	if (gFixedFrameTimeCount > gMaxFixedFrameTime)
	{
		gFixedFrameTimeCount = 0.0f;

		// Check if open list is empty.
		if (!gpMapData->IsOpenListEmpty())
		{
			// Hide last current node on map.
			gpMapView->HideCurrentNode(gpMapData->GetCurrentNode());

			// Update current node position.
			gpMapData->UpdateCurrentNode();

			// Show new current node on map.
			gpMapView->ShowCurrentNode(gpMapData->GetCurrentNode());

			// Run search.
			bool foundPath = gpSearchMethods[gSearchMethodIndex]->FindPath(
				             gpMapData->GetMap(), gpMapData->GetMapSize(), gpMapData->GetGoalNode(),
				             gpMapData->GetOpenList(), gpMapData->GetClosedList(), gpMapData->GetPathList(), 
				             gSearchCount, gSearchListSortCount);

			if (!foundPath)
			{
				// Update map node lists.
				gpMapView->UpdateMapNodes(gpMapView->GetOpenListMapNodes(), gpMapData->GetOpenList());
				gpMapView->UpdateMapNodes(gpMapView->GetClosedListMapNodes(), gpMapData->GetClosedList());

				// Show new nodes on map.
				gpMapView->ShowNodes(gpMapView->GetOpenListMapNodes());
			}
			else
			{
				cout << "\n Path found!";
				CSearchUtility::DisplayList(" Path", gpMapData->GetPathList());

				// Save path coordinates to output file.
				gpMapData->SavePath(gpMapData->GetPathList());

				// Update path node list.
				gpMapView->UpdateMapNodes(gpMapView->GetPathListMapNodes(), gpMapData->GetPathList());

				// Disable controls.
				gpPlayButton->SetState(EButtonState::Disabled);
				gpPauseButton->SetState(EButtonState::Disabled);
				gpStopButton->SetState(EButtonState::Disabled);
				gpStepButton->SetState(EButtonState::Disabled);
				gpFastForwardButton->SetState(EButtonState::Disabled);

				// Show path to goal.
				gpMapView->ShowGoalPath();

				// Check if path to goal is above minimum.
				vector<CNode*> pathNodes = gpMapView->GetPathListMapNodes();
				vector<SPoint> pathPoints;
				if (pathNodes.size() >= MIN_PATH_POINTS)
				{
					pathPoints = gpMapView->GetSmoothPath(pathNodes);
				}
				else
				{
					pathPoints = gpMapView->GetNormalPath(pathNodes);
				}

				// TEMP - REMOVE
				/*IMesh* nodeMesh = gpEngine->LoadMesh("Node.x");
				for (const auto& point : pathPoints)
				{
					IModel* node = nodeMesh->CreateModel(point.mX, point.mY, point.mZ);
					node->Scale(0.5f);
					node->SetSkin("YellowNode.png");
				}*/

				// Set tank position.
				gpTank->SetPathPoints(pathPoints);

				// Set tank to move.
				gpTank->SetState(ETankState::Move);

				// Disable search.
				gSearchActive = false;

				// Update search state to finished.
				gSearchState = ESearchState::Finished;
			}
		}
		else
		{
			cout << "\n No path found.";

			// Disable controls.
			gpPauseButton->SetState(EButtonState::Disabled);
			gpStopButton->SetState(EButtonState::Disabled);
			gpFastForwardButton->SetState(EButtonState::Disabled);

			// Hide current node on map.
			gpMapView->HideCurrentNode(gpMapData->GetCurrentNode());

			// Get position of the node at start.
			CVector3 startNodePos = gpMapView->GetMapNodePosition(gpMapData->GetStartNode());

			// Set the tank on the start pos.
			gpTank->SetStartPos(startNodePos);

			// Set tank to done.
			gpTank->SetState(ETankState::Done);

			// Disable search.
			gSearchActive = false;

			// Update search state to finished.
			gSearchState = ESearchState::Finished;
		}
	}

	if (gpPauseButton->IsActive() && gpPauseButton->Clicked(mouseX, mouseY))
	{
		gpPauseButton->SetState(EButtonState::Disabled);
		gpFastForwardButton->SetState(EButtonState::Disabled);

		gpPlayButton->SetState(EButtonState::Enabled);
		gpStepButton->SetState(EButtonState::Enabled);

		gSearchState = ESearchState::Paused;
	}
	else if (gpStopButton->IsActive() && gpStopButton->Clicked(mouseX, mouseY))
	{
		gpPauseButton->SetState(EButtonState::Disabled);
		gpStopButton->SetState(EButtonState::Disabled);
		gpStepButton->SetState(EButtonState::Disabled);
		gpFastForwardButton->SetState(EButtonState::Disabled);

		// Reset nodes.
		gpMapView->ResetListNodes();
		gpMapData->ResetLists();

		// Disable search.
		gSearchActive = false;

		gpLeftSelectButton->SetState(EButtonState::Enabled);
		gpRightSelectButton->SetState(EButtonState::Enabled);
		gpLoadMapButton->SetState(EButtonState::Enabled);
		gpLoadCoordsButton->SetState(EButtonState::Enabled);
		gpPlayButton->SetState(EButtonState::Enabled);

		gSearchState = ESearchState::Stopped;
	}
	else if (gpFastForwardButton->IsActive() && gpFastForwardButton->Clicked(mouseX, mouseY))
	{
		gFixedFrameTimeCount = 0.0f;

		// Increase search speed (x2).
		gMaxFixedFrameTime = MAX_FIXED_FRAME_TIME_X2;

		gpFastForwardButton->SetState(EButtonState::Disabled);
	}
}

void SearchPause(float& frameTime, int& mouseX, int& mouseY)
{
	if (gpPlayButton->IsActive() && gpPlayButton->Clicked(mouseX, mouseY))
	{
		gpPlayButton->SetState(EButtonState::Disabled);
		gpStepButton->SetState(EButtonState::Disabled);

		gFixedFrameTimeCount = 0.0f;

		// Decrease search speed (x1).
		gMaxFixedFrameTime = MAX_FIXED_FRAME_TIME_X1;

		gpPauseButton->SetState(EButtonState::Enabled);
		gpFastForwardButton->SetState(EButtonState::Enabled);

		gSearchState = ESearchState::Playing;
	}
	else if (gpStopButton->IsActive() && gpStopButton->Clicked(mouseX, mouseY))
	{
		gpStopButton->SetState(EButtonState::Disabled);
		gpStepButton->SetState(EButtonState::Disabled);

		// Reset nodes.
		gpMapView->ResetListNodes();
		gpMapData->ResetLists();

		gSearchActive = false;

		gpLeftSelectButton->SetState(EButtonState::Enabled);
		gpRightSelectButton->SetState(EButtonState::Enabled);
		gpLoadMapButton->SetState(EButtonState::Enabled);
		gpLoadCoordsButton->SetState(EButtonState::Enabled);
		gpPlayButton->SetState(EButtonState::Enabled);

		gSearchState = ESearchState::Stopped;
	}
	else if (gpStepButton->IsActive() && gpStepButton->Clicked(mouseX, mouseY))
	{
		// Check if open list is empty.
		if (!gpMapData->IsOpenListEmpty())
		{
			// Hide last current node on map.
			gpMapView->HideCurrentNode(gpMapData->GetCurrentNode());

			// Update current node position.
			gpMapData->UpdateCurrentNode();

			// Show new current node on map.
			gpMapView->ShowCurrentNode(gpMapData->GetCurrentNode());

			// Run search.
			bool foundPath = gpSearchMethods[gSearchMethodIndex]->FindPath(
				             gpMapData->GetMap(), gpMapData->GetMapSize(), gpMapData->GetGoalNode(),
				             gpMapData->GetOpenList(), gpMapData->GetClosedList(), gpMapData->GetPathList(), 
				             gSearchCount, gSearchListSortCount);

			if (!foundPath)
			{
				// Update map node lists.
				gpMapView->UpdateMapNodes(gpMapView->GetOpenListMapNodes(), gpMapData->GetOpenList());
				gpMapView->UpdateMapNodes(gpMapView->GetClosedListMapNodes(), gpMapData->GetClosedList());

				// Show new nodes on map.
				gpMapView->ShowNodes(gpMapView->GetOpenListMapNodes());
			}
			else
			{
				cout << "\n Path found!";

				// Save path coordinates to output file.
				gpMapData->SavePath(gpMapData->GetPathList());

				// Update path node list.
				gpMapView->UpdateMapNodes(gpMapView->GetPathListMapNodes(), gpMapData->GetPathList());

				// Disable controls.
				gpPlayButton->SetState(EButtonState::Disabled);
				gpStopButton->SetState(EButtonState::Disabled);
				gpStepButton->SetState(EButtonState::Disabled);

				// Show path.
				gpMapView->ShowGoalPath();

				// Check if path to goal is above minimum.
				vector<CNode*> pathNodes = gpMapView->GetPathListMapNodes();
				vector<SPoint> pathPoints;
				if (pathNodes.size() >= MIN_PATH_POINTS)
				{
					pathPoints = gpMapView->GetSmoothPath(pathNodes);
				}
				else
				{
					pathPoints = gpMapView->GetNormalPath(pathNodes);
				}

				// Set tank position.
				gpTank->SetPathPoints(pathPoints);

				// Set tank to move.
				gpTank->SetState(ETankState::Move);

				// Disable search.
				gSearchActive = false;

				// Update search state to finished.
				gSearchState = ESearchState::Finished;
			}
		}
		else
		{
			cout << "\n No path found.";

			// Disable controls.
			gpPlayButton->SetState(EButtonState::Disabled);
			gpStopButton->SetState(EButtonState::Disabled);
			gpStepButton->SetState(EButtonState::Disabled);

			// Hide current node on map.
			gpMapView->HideCurrentNode(gpMapData->GetCurrentNode());

			// Get position of the node at start.
			CVector3 startNodePos = gpMapView->GetMapNodePosition(gpMapData->GetStartNode());

			// Set the tank on the start position.
			gpTank->SetStartPos(startNodePos);

			// Set tank to done.
			gpTank->SetState(ETankState::Done);

			// Disable search.
			gSearchActive = false;

			// Update search state to finished.
			gSearchState = ESearchState::Finished;
		}
	}
}

void SearchFinish(float& frameTime, int& mouseX, int& mouseY)
{
	// Check tank has got to goal.
	if (gpTank->IsState(ETankState::Done))
	{
		// Set the tank status to wait and hide.
		gpTank->SetState(ETankState::Wait);

		gpLeftSelectButton->SetState(EButtonState::Enabled);
		gpRightSelectButton->SetState(EButtonState::Enabled);
		gpLoadMapButton->SetState(EButtonState::Enabled);
		gpLoadCoordsButton->SetState(EButtonState::Enabled);
		gpPlayButton->SetState(EButtonState::Enabled);

		// Update search state to stopped.
		gSearchState = ESearchState::Stopped;
	}

	// Move tank towards goal.
	gpTank->Update(frameTime);
}

// Sets the error flag to true.
void SetErrorFlag()
{
	gErrorFlag = true;
}

// Clears the error flag (if true).
void ClearErrorFlag()
{
	if (gErrorFlag)
	{
		gErrorFlag = false;
	}
}

// Selects the previous search method in the search array.
// Updates the search method text in HUD.
void PreviousSearchMethod()
{
	if (gSearchMethodIndex > 0)
	{
		gSearchMethodIndex -= 1;
	}
	else
	{
		gSearchMethodIndex = (TOTAL_SEARCH_METHODS - 1);
	}

	gSearchMethodName = gpSearchMethods[gSearchMethodIndex]->GetName();
}

// Selects the next search method in the search array.
// Updates the search method text in HUD.
void NextSearchMethod()
{
	if (gSearchMethodIndex < (TOTAL_SEARCH_METHODS - 1))
	{
		gSearchMethodIndex += 1;
	}
	else
	{
		gSearchMethodIndex = 0;
	}

	gSearchMethodName = gpSearchMethods[gSearchMethodIndex]->GetName();
}
