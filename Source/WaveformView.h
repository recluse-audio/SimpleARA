/*
  ==============================================================================

    WaveformView.h
    Created: 20 Nov 2022 4:14:38pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformView  : public juce::Component
{
public:
    WaveformView();
    ~WaveformView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformView)
};
