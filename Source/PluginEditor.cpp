/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DocumentView.h"
#include "ARA_DocumentSpecialisation.h"
#include "ARA_PlaybackRegion.h"
#include "ARAViewSection.h"
#include "ControlPanel.h"
#include "TopControlPanel.h"
#include "HelperDisplay.h"

//==============================================================================
SimpleARAEditor::SimpleARAEditor (SimpleARAProcessor& p)
    : AudioProcessorEditor (&p), AudioProcessorEditorARAExtension(&p), audioProcessor (p)
{

	
    araViewSection = std::make_unique<ARAViewSection>(*this);
    addAndMakeVisible(araViewSection.get());
    controlPanel = std::make_unique<ControlPanel>(*this);
    addAndMakeVisible(controlPanel.get());
    topControlPanel = std::make_unique<TopControlPanel>();
    addAndMakeVisible(topControlPanel.get());
	helperDisplay = std::make_unique<HelperDisplay>();
	addAndMakeVisible(helperDisplay.get());
	
	// ARA requires that plugin editors are resizable to support tight integration
	// into the host UI
	setResizable (true, false);
	setSize (400, 300);
}

SimpleARAEditor::~SimpleARAEditor()
{
    auto viewSelection = this->getARAEditorView()->getViewSelection();
    const auto& playbackRegions = viewSelection.getPlaybackRegions<ARA_PlaybackRegion>();
    for(auto region : playbackRegions)
    {
        region->setCurrentlyInView(false);
    }
}

//==============================================================================
void SimpleARAEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey.darker());
}

void SimpleARAEditor::resized()
{
	if (documentView != nullptr)
		documentView->setBoundsRelative(0.f, 0.f, 1.f, 1.f);
	
	if(helperDisplay != nullptr)
		helperDisplay->setBoundsRelative(0.f, 0.9f, 0.4f, 0.1f);
    
    controlPanel->setBoundsRelative(0.f, 0.f, 0.2f, 1.f);
    topControlPanel->setBoundsRelative(0.2f, 0.f, 0.8f, 0.1f);
    araViewSection->setBoundsRelative(0.2f, 0.1f, 0.8f, 0.8f);
    helperDisplay->setBoundsRelative(0.2f, 0.9f, 0.8f, 0.1f);
}




HelperDisplay* SimpleARAEditor::getHelperDisplay()
{
	return helperDisplay.get();
}

SimpleARAProcessor& SimpleARAEditor::getSimpleAudioProcessor() const
{
    return audioProcessor;
}

PlayHeadState& SimpleARAEditor::getPlayHeadState()
{
    return audioProcessor.playHeadState;
}

juce::ARADocument* SimpleARAEditor::getARADocument()
{
    juce::ARADocument* araDocument = nullptr;
    
    auto specialisation = this->getARADocumentSpecialisation();
    if(specialisation != nullptr)
    {
        araDocument = specialisation->getDocument();
        return araDocument;
    }
    
    jassert(araDocument != nullptr);
    return araDocument;

}

ARA_DocumentSpecialisation* SimpleARAEditor::getARADocumentSpecialisation()
{
    ARA_DocumentSpecialisation* araDocumentSpecialisation = nullptr;
    
    if (auto* editorView = this->getARAEditorView())
    {
        araDocumentSpecialisation = ARADocumentControllerSpecialisation::getSpecialisedDocumentController<ARA_DocumentSpecialisation>(editorView->getDocumentController());
        
        return araDocumentSpecialisation;
    }
    
    jassert(araDocumentSpecialisation != nullptr);
    
    return araDocumentSpecialisation;
}
