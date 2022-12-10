/*
  ==============================================================================

    TopControlPanel.h
    Created: 2 Dec 2022 6:37:49pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class SimpleARAEditor;

//==============================================================================
/*
*/
class TopControlPanel  : public juce::Component
, public juce::Button::Listener
{
public:
    TopControlPanel(SimpleARAEditor& editor);
    ~TopControlPanel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* b) override;
private:
    std::unique_ptr<juce::TextButton> undoButton;
    std::unique_ptr<juce::TextButton> redoButton;
    
    SimpleARAEditor& mEditor;
    juce::UndoManager& undoManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TopControlPanel)
};
