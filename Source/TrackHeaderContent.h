/*
  ==============================================================================

    TrackHeaderContent.h
    Created: 2 Jan 2023 11:03:50am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MultiTrackObjectBase.h"
class TrackHeader;
class TrackData;
class MultiTrackTimeline;
//==============================================================================
/*
*/
class TrackHeaderContent  : public juce::Component,
                            public MultiTrackObjectBase
{
public:
    TrackHeaderContent(MultiTrackTimeline& timeLine);
    ~TrackHeaderContent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void updateZoomState() override;

    void addTrackHeader(Track* trackToMakeHeaderFor);
    
private:
    juce::OwnedArray<TrackHeader> trackHeaders;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackHeaderContent)
};
