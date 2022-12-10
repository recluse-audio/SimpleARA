/*
  ==============================================================================

    TopControlPanel.cpp
    Created: 2 Dec 2022 6:37:49pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TopControlPanel.h"
#include "PluginEditor.h"
#include "ARA_DocumentSpecialisation.h"

//==============================================================================
TopControlPanel::TopControlPanel(SimpleARAEditor& editor)
: mEditor(editor)
, undoManager(editor.getARADocumentSpecialisation()->getUndoManager())
{
    undoButton = std::make_unique<juce::TextButton>("UNDO");
    undoButton->addListener(this);
    addAndMakeVisible(undoButton.get());
    
    redoButton = std::make_unique<juce::TextButton>("REDO");
    redoButton->addListener(this);
    addAndMakeVisible(redoButton.get());

    
}

TopControlPanel::~TopControlPanel()
{
}

void TopControlPanel::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::aquamarine.darker().withAlpha(0.7f));
}

void TopControlPanel::resized()
{
    undoButton->setBoundsRelative(0.8f, 0.1f, 0.1f, 0.8f);
    redoButton->setBoundsRelative(0.9f, 0.1f, 0.1f, 0.8f);

}

void TopControlPanel::buttonClicked(juce::Button *b)
{
    if(b == undoButton.get())
    {
        undoManager.undo();
    }
    if(b == redoButton.get())
    {
        undoManager.redo();
    }
}
