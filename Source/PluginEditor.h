/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class HelperDisplay;


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

private:
	std::unique_ptr<juce::Component> documentView;
	std::unique_ptr<HelperDisplay> helperDisplay; // print address of object when being hovered over
	
    SimpleARAProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleARAEditor)
};
