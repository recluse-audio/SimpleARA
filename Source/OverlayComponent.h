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

class MultiTrackTimeLine;
//==============================================================================
/*
    Catches clicks and draw the transport playhead
*/
class OverlayComponent : public juce::Component,
private juce::Timer
{
public:
    class PlayheadMarkerComponent : public juce::Component
    {
        void paint (juce::Graphics& g) override { g.fillAll (juce::Colours::yellow.darker (0.2f)); }
    };

	OverlayComponent (MultiTrackTimeLine& timeLine);

	~OverlayComponent() override;
	
	void resized() override;

	void setZoomLevel (double pixelPerSecondIn);

	void setHorizontalOffset (int offset);
	
	void updateZoomState();

private:
	MultiTrackTimeLine& mTimeLine;

	void doResize();

	void timerCallback() override;

    static constexpr double markerWidth = 2.0;

    double pixelPerSecond = 1.0;
    int horizontalOffset = 0;
    PlayheadMarkerComponent playheadMarker;
	
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OverlayComponent)
};
