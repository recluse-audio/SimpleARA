/*
  ==============================================================================

    TrackRegion.h
    Created: 16 Dec 2022 6:15:52pm
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
class TrackRegion : public juce::Component
{
public:
    TrackRegion();
    ~TrackRegion() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    virtual juce::Range<double>* getRangeInSeconds() const;
    double getDuration() const;

    
private:
    std::unique_ptr<juce::Range<double>> rangeInSeconds;
    
    juce::Colour bgColor {75, 75, 75};
    juce::Colour outlineColor { 230, 230, 230 };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackRegion)
};
