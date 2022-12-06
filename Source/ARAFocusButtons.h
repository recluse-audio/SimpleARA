/*
  ==============================================================================

    ARAFocusButtons.h
    Created: 5 Dec 2022 2:17:34pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
    A set of radio buttons controlling the "focus" of the ARAViewSection
        Switch between Document / Sequence / Region
*/
class ARAFocusButtons  : public juce::Component
{
public:
    ARAFocusButtons();
    ~ARAFocusButtons() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::unique_ptr<juce::TextButton> documentButton;
    std::unique_ptr<juce::TextButton> sequenceButton;
    std::unique_ptr<juce::TextButton> regionButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARAFocusButtons)
};
