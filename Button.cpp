
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: Button.cpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Implements button object functions.

**************************************************************************************************/

#include "Button.hpp"

// Constructor. Sets button sprite, state and click area.
CButton::CButton(ISprite* pSprite, const EButtonState& buttonState, const float& buttonWidth, 
	             const float& buttonHeight)
{
	mpSprite = pSprite;
	mButtonState = buttonState;

	mButtonClickArea.mMinX = mpSprite->GetX();
	mButtonClickArea.mMaxX = mpSprite->GetX() + buttonWidth;
	mButtonClickArea.mMinY = mpSprite->GetY();
	mButtonClickArea.mMaxY = mpSprite->GetY() + buttonHeight;

	if (buttonState == EButtonState::Enabled)
	{
		mpSprite->SetZ(BUTTON_SHOW_POS_Z);
	}
	else if (buttonState == EButtonState::Disabled)
	{
		mpSprite->SetZ(BUTTON_HIDE_POS_Z);
	}
}

// Destructor.
CButton::~CButton() {}

// Checks if the button state is active.
bool CButton::IsActive()
{
	if (mButtonState == EButtonState::Enabled)
	{
		return true;
	}

	return false;
}

// Checks if the button has been clicked.
bool CButton::Clicked(int& kMousePosX, int& kMousePosY)
{
	if (kMousePosX > mButtonClickArea.mMinX && kMousePosX < mButtonClickArea.mMaxX &&
		kMousePosY > mButtonClickArea.mMinY && kMousePosY < mButtonClickArea.mMaxY)
	{
		return true;
	}

	return false;
}

// Sets the button state.
void CButton::SetState(const EButtonState& buttonState)
{
	if (buttonState == EButtonState::Enabled)
	{
		mpSprite->SetZ(BUTTON_SHOW_POS_Z);
		mButtonState = EButtonState::Enabled;
	}
	else if (buttonState == EButtonState::Disabled)
	{
		mpSprite->SetZ(BUTTON_HIDE_POS_Z);
		mButtonState = EButtonState::Disabled;
	}
}

// Gets the sprite.
ISprite* CButton::GetSprite()
{
	return mpSprite;
}