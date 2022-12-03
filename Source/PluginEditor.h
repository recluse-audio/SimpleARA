/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class ARAViewSection;
class TopControlPanel;
class ControlPanel;
class HelperDisplay;
class ARA_DocumentSpecialisation;


//==============================================================================
/**
*/
class SimpleARAEditor  : public juce::AudioProcessorEditor,
public juce::AudioProcessorEditorARAExtension
{
public:
    SimpleARAEditor (SimpleARAProcessor&);
    ~SimpleARAEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

	HelperDisplay* getHelperDisplay();
    SimpleARAProcessor& getSimpleAudioProcessor() const;
    PlayHeadState& getPlayHeadState();
    juce::ARADocument* getARADocument();
    ARA_DocumentSpecialisation* getARADocumentSpecialisation();

private:
	std::unique_ptr<juce::Component> documentView;
    std::unique_ptr<ARAViewSection> araViewSection;
    std::unique_ptr<ControlPanel>   controlPanel;
    std::unique_ptr<TopControlPanel> topControlPanel;
	std::unique_ptr<HelperDisplay> helperDisplay; // print address of object when being hovered over
	
    SimpleARAProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleARAEditor)
};
