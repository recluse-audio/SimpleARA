/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DocumentView.h"
#include "ARA_DocumentSpecialisation.h"
#include "HelperDisplay.h"

//==============================================================================
SimpleARAEditor::SimpleARAEditor (SimpleARAProcessor& p)
    : AudioProcessorEditor (&p), AudioProcessorEditorARAExtension(&p), audioProcessor (p)
{
	if (auto* editorView = getARAEditorView())
	{
		auto* document = ARADocumentControllerSpecialisation::getSpecialisedDocumentController<ARA_DocumentSpecialisation>(editorView->getDocumentController())->getDocument();
		documentView = std::make_unique<DocumentView> (*this, *document, p.playHeadState );
	}

	addAndMakeVisible (documentView.get());
	
	helperDisplay = std::make_unique<HelperDisplay>();
	addAndMakeVisible(helperDisplay.get());
	
	// ARA requires that plugin editors are resizable to support tight integration
	// into the host UI
	setResizable (true, false);
	setSize (400, 300);
}

SimpleARAEditor::~SimpleARAEditor()
{
}

//==============================================================================
void SimpleARAEditor::paint (juce::Graphics& g)
{
	auto outline = this->getBounds();
	g.setColour(juce::Colours::blue);
	g.drawRect(outline, 2.f);


	g.setColour (Colours::white);
	g.setFont (15.0f);
	g.drawFittedText ("Audio Processor Editor",
					  getLocalBounds(),
					  Justification::centred,
					  1);
	
	if (! isARAEditorView())
	{
		g.setColour (Colours::white);
		g.setFont (15.0f);
		g.drawFittedText ("ARA host isn't detected. This plugin only supports ARA mode",
						  getLocalBounds(),
						  Justification::centred,
						  1);
	}
}

void SimpleARAEditor::resized()
{
	if (documentView != nullptr)
		documentView->setBoundsRelative(0.f, 0.f, 1.f, 1.f);
	
	if(helperDisplay != nullptr)
		helperDisplay->setBoundsRelative(0.f, 0.9f, 0.4f, 0.1f);
}




HelperDisplay* SimpleARAEditor::getHelperDisplay()
{
	return helperDisplay.get();
}
