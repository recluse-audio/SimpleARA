/*
  ==============================================================================

    ControlPanel.h
    Created: 2 Dec 2022 6:35:05pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class SimpleARAEditor;
class NavigationMenu;
class ARAFocusButtons;
//==============================================================================
/**
    This class represents the control panel on the left side of the plugin
 
    The navigation menu represents the ARA playback regions organized by region sequence
*/
class ControlPanel  : public juce::Component
{
public:
    ControlPanel(SimpleARAEditor& editor);
    ~ControlPanel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SimpleARAEditor& mEditor;
    std::unique_ptr<NavigationMenu> navigationMenu;
    std::unique_ptr<ARAFocusButtons> focusButtons;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlPanel)
};
