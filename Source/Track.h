/*
  ==============================================================================

    Track.h
    Created: 23 Dec 2022 10:27:54am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MultiTrackObjectBase.h"

class MultiTrackTimeline;
class TrackLane;
class TrackHeader;
class ZoomState;

//==============================================================================
/*
*/
class Track  : public juce::Component
{
public:
    Track();
    ~Track() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void updateZoomState(ZoomState& zoomState);
    
    void setTrackName(juce::StringRef newName);
    
    double getDuration() const;
private:
    std::unique_ptr<TrackLane> trackLane;
    std::unique_ptr<TrackHeader> trackHeader;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Track)
};
