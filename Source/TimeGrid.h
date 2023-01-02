/*
  ==============================================================================

    TimeGrid.h
    Created: 22 Dec 2022 3:45:19pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class MultiTrackTimeline;
//==============================================================================
/*
*/
class TimeGrid  : public juce::Component
{
public:
    TimeGrid(MultiTrackTimeline& timeLine);
    ~TimeGrid() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    MultiTrackTimeline& mTimeline;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeGrid)
};
