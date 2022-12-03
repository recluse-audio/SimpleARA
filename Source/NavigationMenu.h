/*
  ==============================================================================

    NavigationMenu.h
    Created: 2 Dec 2022 7:29:37pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
    A menu for navigating the ARA objects in the document
    
     This component is essentally a button and a prepared menu unique to this use-case
      More for organizing code than anything else.  Not worth inheriting from, not worth marking final
*/
class NavigationMenu  : public juce::Component
, public juce::Button::Listener
{
public:
    NavigationMenu(juce::ARADocument& document);
    ~NavigationMenu() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** Shows menu */
    void buttonClicked(juce::Button* b) override;
    

private:
    std::unique_ptr<juce::TextButton> menuButton;
    std::unique_ptr<juce::PopupMenu> popupMenu;
    
    juce::ARADocument& araDocument;
    
    //
    void _prepareMenu();
    juce::PopupMenu* _makeRegionSequenceMenu(juce::ARARegionSequence* regionSequence);


    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NavigationMenu)
};
