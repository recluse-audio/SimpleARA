/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


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

private:
	std::unique_ptr<juce::Component> documentView;
	
	
    SimpleARAProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleARAEditor)
};
