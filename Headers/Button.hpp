
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: Button.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Defines a button object.

**************************************************************************************************/

#ifndef _BUTTON_H
#define _BUTTON_H

// TL-Engine include file and namespace.
#include <TL-Engine.h>
using namespace tle;

// Width of the text in the HUD.
const float TEXT_BOX_WIDTH = 270.0f;

// Size of a button in the HUD.
const float BUTTON_SIZE = 50.0f;

// Width of a select button type.
const float SELECT_BUTTON_WIDTH = 25.0f;

// Spacing amount for a button.
const float BUTTON_SPACER = 10.0f;

// Sprite layer Z orders.
const float HUD_POS_Z = 0.1f;
const float TEXT_BOX_POS_Z = 0.0f;
const float BUTTON_SHOW_POS_Z = 0.0f;
const float BUTTON_HIDE_POS_Z = 0.2f;

// Texture file names.
const string LEFT_SELECT_BUTTON_TEX = "LeftSelectButton.png";
const string RIGHT_SELECT_BUTTON_TEX = "RightSelectButton.png";
const string MAP_BUTTON_TEX = "MapButton.png";
const string COORDS_BUTTON_TEX = "CoordsButton.png";
const string PLAY_BUTTON_TEX = "PlayButton.png";
const string PAUSE_BUTTON_TEX = "PauseButton.png";
const string STOP_BUTTON_TEX = "StopButton.png";
const string STEP_BUTTON_TEX = "StepButton.png";
const string FAST_FORWARD_BUTTON_TEX = "FastForwardButton.png";
const string TEXT_BOX_TEX = "TextBox.png";

// The states of a button.
enum EButtonState
{
	Enabled,
	Disabled
};

// Defines a region in the window area, around a button origin.
struct SButtonClickArea
{
	float mMinX;
	float mMinY;
	float mMaxX;
	float mMaxY;
};

class CButton
{

public:

	// Constructor. Sets button sprite, state and click area.
	// Param: Button sprite, Button state, Button width, button height.
	// Return: Button object.
	CButton(ISprite* pSprite, const EButtonState& buttonState, const float& buttonWidth, 
		    const float& buttonHeight);

	// Destructor.
	// Param:
	// Return:
	~CButton();

	// Checks if the button state is active.
	// Param:
	// Return: True or false.
	bool IsActive();

	// Checks if the button has been clicked.
	// Param: Mouse X position, Mouse Y position.
	// Return: True or false.
	bool Clicked(int& mousePosX, int& mousePosY);

	// Sets the button state.
	// Param: Button state.
	// Return:
	void SetState(const EButtonState& buttonState);

	// Gets the sprite pointer.
	// Param:
	// Return: Sprite.
	ISprite* GetSprite();

private:

	EButtonState mButtonState;
	SButtonClickArea mButtonClickArea;
	ISprite* mpSprite;

};

#endif  // _BUTTON_H
