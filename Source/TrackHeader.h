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
class TrackHeader : public juce::Component,
                    public MultiTrackObjectBase
{
public:
	explicit TrackHeader (MultiTrackTimeline& timeLine);
	
	void resized() override;
	void paint (juce::Graphics& g) override;
    
    void setName(juce::StringRef newName);
    void updateZoomState() override;
    void setHeaderWidth(int newWidth);
private:
    int headerWidth = 0;
	juce::Label trackNameLabel;
};
