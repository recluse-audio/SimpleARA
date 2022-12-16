/*
  ==============================================================================

    MultiTrackTimeline.h
    Created: 15 Dec 2022 6:20:05pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class TrackLane;
//==============================================================================
/*
    Base class for a component that handles scrollable timelines
    This is essentially the editor mode of a DAW
*/
class MultiTrackTimeline  : public juce::Component
{
public:
    MultiTrackTimeline();
    ~MultiTrackTimeline() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::OwnedArray<std::unique_ptr<TrackLane>> trackLanes;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiTrackTimeline)
};
