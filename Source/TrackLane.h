/*
  ==============================================================================

    TrackLane.h
    Created: 15 Dec 2022 6:31:50pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MultiTrackObjectBase.h"
class TrackRegion;
//==============================================================================
/*
    This class represents one track in a multi track timeline.
 
    It is meant to be interface well with playhead and timeline positions
*/
class TrackLane : public juce::Component
{
public:
    TrackLane();
    ~TrackLane() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void addRegion(TrackRegion* region);
    void removeRegion(TrackRegion* region);

    
    virtual float getDuration() const;
    
	void updateZoomState(ZoomState* zoomState);
    
    void generateThreeRandomRegions();
protected:
    int orderIndex;
    float duration = 120.f;
    
    // Looks at the end position (in seconds) of every region starting with the last added
    void _updateDuration();

private:
    juce::OwnedArray<TrackRegion> regionArray;
    
    juce::Colour bgColor {55, 55, 55};
    juce::Colour outlineColor { 230, 230, 230 };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackLane)
};
