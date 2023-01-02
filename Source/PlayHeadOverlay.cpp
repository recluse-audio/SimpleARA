/*
  ==============================================================================

    OverlayComponent.cpp
    Created: 1 Nov 2022 12:50:25pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayHeadOverlay.h"
#include "MultiTrackTimeline.h"

class PlayheadMarker : public juce::Component
{
    void paint (juce::Graphics& g) override { g.fillAll (juce::Colours::yellow.darker (0.2f)); }
};

//==============================================================================
PlayHeadOverlay::PlayHeadOverlay(MultiTrackTimeline& timeLine)
: mTimeline(timeLine)
{
    playheadMarker = std::unique_ptr<PlayheadMarker>();
	addChildComponent (playheadMarker.get());
	setInterceptsMouseClicks (false, false);
	startTimerHz (30);
}

PlayHeadOverlay::~PlayHeadOverlay()
{
	stopTimer();
}

void PlayHeadOverlay::resized()
{
	doResize();
}


void PlayHeadOverlay::setZoomLevel(double pixelPerSecondIn)
{
	pixelPerSecond = pixelPerSecondIn;
}

void PlayHeadOverlay::setHorizontalScrollOffset (int offset)
{
	horizontalScrollOffset = offset;
}


//========================
// PRIVATE FUNCTIONS
void PlayHeadOverlay::doResize()
{
    PlayHeadState& playHeadState = mTimeline.getPlayHeadState();
	
	if (playHeadState.isPlaying.load())
	{
		const auto markerX = playHeadState.timeInSeconds.load() * pixelPerSecond;
		const auto playheadLine = getLocalBounds().withTrimmedLeft ((int) (markerX - markerWidth / 2.0) - horizontalScrollOffset)
												  .removeFromLeft ((int) markerWidth);
		playheadMarker->setVisible (true);
		playheadMarker->setBounds (playheadLine);
	}
	else
	{
		playheadMarker->setVisible (false);
	}
}

void PlayHeadOverlay::timerCallback()
{
	doResize();
}
