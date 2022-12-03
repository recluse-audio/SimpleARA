/*
  ==============================================================================

    ControlPanel.cpp
    Created: 2 Dec 2022 6:35:05pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ControlPanel.h"
#include "PluginEditor.h"
#include "NavigationMenu.h"
#include "ARA_DocumentSpecialisation.h"
//==============================================================================
ControlPanel::ControlPanel(SimpleARAEditor& editor) : mEditor(editor)
{
    if (auto* editorView = mEditor.getARAEditorView())
    {
        
        auto* document = ARADocumentControllerSpecialisation::getSpecialisedDocumentController<ARA_DocumentSpecialisation>(editorView->getDocumentController())->getDocument();
        
        navigationMenu = std::make_unique<NavigationMenu>(*document);
        addAndMakeVisible(navigationMenu.get());
    }
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::coral.withAlpha(0.7f));
}

void ControlPanel::resized()
{
    navigationMenu->setBoundsRelative(0.2f, 0.2f, 0.6f, 0.2f);

}
