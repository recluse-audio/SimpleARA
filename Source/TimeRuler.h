/*
  ==============================================================================

    TimeRuler.h
    Created: 14 Dec 2022 6:37:00pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TimeRuler  : public juce::Component
{
public:
    TimeRuler();
    ~TimeRuler() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeRuler)
};
