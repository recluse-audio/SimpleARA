/*
  ==============================================================================

    TimeRuler.h
    Created: 21 Dec 2022 2:26:06pm
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
class TimeRuler  : public juce::Component,
                    public MultiTrackObjectBase
{
public:
    TimeRuler(MultiTrackTimeline& timeLine);
    ~TimeRuler() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void updateZoomState() override;
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeRuler)
};
