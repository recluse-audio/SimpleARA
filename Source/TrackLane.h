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
class MultiTrackTimeline;
//==============================================================================
/*
    This class represents one track in a multi track timeline.
 
    It is meant to be interface well with playhead and timeline positions
*/
class TrackLane
: public juce::Component
, public MultiTrackObjectBase
{
public:
    TrackLane(MultiTrackTimeline& timeLine);
    explicit TrackLane(MultiTrackTimeline& timeLine, int index);
    ~TrackLane() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void addRegion(TrackRegion* region);
    void removeRegion(TrackRegion* region);
    
    void setOrderIndex(int newIndex) override;
    int getOrderIndex() const override;
    
    virtual float getDuration() const;
    
	void updateZoomState() override;
    virtual void setZoomLevel(double pixelsPerSecond);
    
protected:
    int orderIndex;
    float duration = 120.f;

private:
    std::unique_ptr<juce::Label> trackLabel;
    juce::OwnedArray<TrackRegion> trackRegions;
    
    juce::Colour bgColor {55, 55, 55};
    juce::Colour outlineColor { 230, 230, 230 };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackLane)
};
