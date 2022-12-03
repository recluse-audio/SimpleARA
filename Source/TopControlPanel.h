/*
  ==============================================================================

    TopControlPanel.h
    Created: 2 Dec 2022 6:37:49pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TopControlPanel  : public juce::Component
{
public:
    TopControlPanel();
    ~TopControlPanel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TopControlPanel)
};
