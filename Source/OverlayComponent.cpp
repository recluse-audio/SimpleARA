/*
  ==============================================================================

    OverlayComponent.cpp
    Created: 1 Nov 2022 12:50:25pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OverlayComponent.h"

//==============================================================================
OverlayComponent::OverlayComponent(PlayHeadState& playHeadStateIn)
: playHeadState (&playHeadStateIn)
{
addChildComponent (playheadMarker);
setInterceptsMouseClicks (false, false);
startTimerHz (30);
}

OverlayComponent::~OverlayComponent()
{
	stopTimer();
}

void OverlayComponent::resized()
{
	doResize();
}


void OverlayComponent::setZoomLevel(double pixelPerSecondIn)
{
	pixelPerSecond = pixelPerSecondIn;
}

void OverlayComponent::setHorizontalOffset (int offset)
{
	horizontalOffset = offset;
}


//========================
// PRIVATE FUNCTIONS
void OverlayComponent::doResize()
{
	if (playHeadState->isPlaying.load())
	{
		const auto markerX = playHeadState->timeInSeconds.load() * pixelPerSecond;
		const auto playheadLine = getLocalBounds().withTrimmedLeft ((int) (markerX - markerWidth / 2.0) - horizontalOffset)
												  .removeFromLeft ((int) markerWidth);
		playheadMarker.setVisible (true);
		playheadMarker.setBounds (playheadLine);
	}
	else
	{
		playheadMarker.setVisible (false);
	}
}

void OverlayComponent::timerCallback() 
{
	doResize();
}
