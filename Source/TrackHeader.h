/*
  ==============================================================================

    TrackHeader.h
    Created: 1 Nov 2022 12:48:57pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MultiTrackObjectBase.h"

class MultiTrackTimeline;
//==============================================================================
/*
*/
class TrackHeader : public juce::Component
{
public:
	explicit TrackHeader ();
	
	void resized() override;
	void paint (juce::Graphics& g) override;
    
    void setName(juce::StringRef newName);
    void updateZoomState(ZoomState& zoomState);
    void setHeaderWidth(int newWidth);
private:
    int headerWidth = 0;
	juce::Label trackNameLabel;
};
