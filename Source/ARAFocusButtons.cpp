/*
  ==============================================================================

    ARAFocusButtons.cpp
    Created: 5 Dec 2022 2:17:34pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ARAFocusButtons.h"
#include "PluginEditor.h"

//==============================================================================
ARAFocusButtons::ARAFocusButtons(SimpleARAEditor& editor)
: mEditor(editor)
{
    documentButton = std::make_unique<juce::TextButton>("Document");
    sequenceButton = std::make_unique<juce::TextButton>("Sequence");
    regionButton  = std::make_unique<juce::TextButton>("Region");

    documentButton->setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::orangered.darker());
    sequenceButton->setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::orangered.darker());
    regionButton->setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::orangered.darker());
    
    documentButton->setClickingTogglesState(true);
    sequenceButton->setClickingTogglesState(true);
    regionButton->setClickingTogglesState(true);
    
    documentButton->setRadioGroupId(1);
    sequenceButton->setRadioGroupId(1);
    regionButton->setRadioGroupId(1);

    addAndMakeVisible(documentButton.get());
    addAndMakeVisible(sequenceButton.get());
    addAndMakeVisible(regionButton.get());
    
    documentButton->addListener(this);
    sequenceButton->addListener(this);
    regionButton->addListener(this);

    updateButtons();
}

ARAFocusButtons::~ARAFocusButtons()
{
}

void ARAFocusButtons::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    
    g.setColour(juce::Colours::orangered.darker());
    g.fillRoundedRectangle(bounds, 2.f);
    
    g.setColour(juce::Colours::whitesmoke);
    g.drawRoundedRectangle(bounds, 2.f, 2.f);
}

void ARAFocusButtons::resized()
{
    documentButton->setBoundsRelative(0.05f, 0.15f, 0.3f, 0.7f);
    sequenceButton->setBoundsRelative(0.35f, 0.15f, 0.3f, 0.7f);
    regionButton->setBoundsRelative(0.65f, 0.15f, 0.3f, 0.7f);


}

//===========================
void ARAFocusButtons::updateButtons()
{
    switch(mEditor.getFocus())
    {
        case Focus::DocumentFocus:
            documentButton->setToggleState(true, juce::NotificationType::dontSendNotification);
        case Focus::SequenceFocus:
            sequenceButton->setToggleState(true, juce::NotificationType::dontSendNotification);
        case Focus::RegionFocus:
            regionButton->setToggleState(true, juce::NotificationType::dontSendNotification);
    }
}


//===========================
void ARAFocusButtons::buttonClicked(juce::Button *b)
{
    if(b == documentButton.get())
    {
        mEditor.setFocus(Focus::DocumentFocus);
    }
    else if (b == sequenceButton.get())
    {
        mEditor.setFocus(Focus::SequenceFocus);
    }
    else if (b == regionButton.get())
    {
        mEditor.setFocus(Focus::RegionFocus);
    }
}
