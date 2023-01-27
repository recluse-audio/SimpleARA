/*
  ==============================================================================

    ZoomControls.h
    Created: 1 Nov 2022 12:48:34pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ZoomState.h"
//==============================================================================
/*
*/
class ZoomControls : public Component
, public juce::Button::Listener
{
public:
    ZoomControls(ZoomState& zState) : zoomState(zState)
    {
		zoomInButton = std::make_unique<juce::TextButton>();
		zoomInButton->setButtonText(" + ");
		zoomInButton->addListener(this);
		addAndMakeVisible (zoomInButton.get());

		zoomOutButton = std::make_unique<juce::TextButton>();
		zoomOutButton->setButtonText(" - ");
		zoomOutButton->addListener(this);
		addAndMakeVisible (zoomOutButton.get());

    }



    void setVertical(bool orientVertically)
    {
        isVertical = orientVertically;
    }
    
    void resized() override
    {
		if(isVertical)
		{
			zoomInButton->setBoundsRelative(0.f, 0.1f, 1.f, 0.35f);
			zoomOutButton->setBoundsRelative(0.f, 0.55f, 1.f, 0.35f);
		}
		else
		{
			zoomInButton->setBoundsRelative(0.55f, 0.f, 0.35f, 1.f);
			zoomOutButton->setBoundsRelative(0.1, 0.f, 0.35f, 1.f);
		}

    }
	
	void buttonClicked(juce::Button* button) override
	{
		if(button == zoomInButton.get())
		{
			if(isVertical)
				zoomState.transformVerticalZoomByPercent(0.1);
			else
				zoomState.transformHorizontalZoomByPercent(0.1);
		}
		if(button == zoomOutButton.get())
		{
			if(isVertical)
				zoomState.transformVerticalZoomByPercent(-0.1);
			else
				zoomState.transformHorizontalZoomByPercent(-0.1);
		}
	}

private:
	ZoomState& zoomState;
    bool isVertical = false;
	std::unique_ptr<juce::TextButton> zoomInButton;
	std::unique_ptr<juce::TextButton> zoomOutButton;

};
