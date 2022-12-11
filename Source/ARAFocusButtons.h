/*
  ==============================================================================

    ARAFocusButtons.h
    Created: 5 Dec 2022 2:17:34pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class SimpleARAEditor;
//==============================================================================
/**
    A set of radio buttons controlling the "focus" of the ARAViewSection
        Switch between Document / Sequence / Region
*/
class ARAFocusButtons  : public juce::Component
, public juce::Button::Listener
{
public:
    ARAFocusButtons(SimpleARAEditor& editor);
    ~ARAFocusButtons() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* b) override;
    /** Makes sure the radio button state matches the ARAViewSection state.  Relevant in save/restore */
    void updateButtons();
private:
    std::unique_ptr<juce::TextButton> documentButton;
    std::unique_ptr<juce::TextButton> sequenceButton;
    std::unique_ptr<juce::TextButton> regionButton;

    SimpleARAEditor& mEditor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARAFocusButtons)
};
