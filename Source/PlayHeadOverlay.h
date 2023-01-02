/*
  ==============================================================================

    OverlayComponent.h
    Created: 1 Nov 2022 12:50:25pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UtilObjects.h"

class MultiTrackTimeline;
class PlayheadMarker;
//==============================================================================
/*
    Draws a vertical line representing the playhead.  
*/
class PlayHeadOverlay : public juce::Component,
private juce::Timer
{
public:


    PlayHeadOverlay (MultiTrackTimeline& timeLine);

	~PlayHeadOverlay() override;
	
	void resized() override;

	void setZoomLevel (double pixelPerSecondIn);

    /** How far we have scrolled along the timeline in pixels */
	void setHorizontalScrollOffset (int offset);
	
	void updateZoomState();

private:
	MultiTrackTimeline& mTimeline;

	void doResize();

	void timerCallback() override;

    static constexpr double markerWidth = 2.0;

    double pixelPerSecond = 1.0;
    int horizontalScrollOffset = 0;
    std::unique_ptr<PlayheadMarker> playheadMarker;
	
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayHeadOverlay)
};
