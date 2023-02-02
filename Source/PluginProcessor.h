/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UtilObjects.h"

//==============================================================================
/**
*/
class SimpleARAProcessor  : public juce::AudioProcessor
, public juce::ValueTree::Listener
#if JucePlugin_Enable_ARA
 , public juce::AudioProcessorARAExtension
#endif
{
public:
    //==============================================================================
    SimpleARAProcessor();
    ~SimpleARAProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	using AudioProcessor::processBlock;
    
   // juce::AudioProcessorValueTreeState& getValueTreeState();
	
	PlayHeadState playHeadState;

private:
	
   // juce::AudioProcessorValueTreeState valueTreeState;
//    juce::AudioProcessorValueTreeState::ParameterLayout _getParameterLayout();
//    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier &property) override;
//    bool valueTreeHasChanged = false;
//    void _updateParameters();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleARAProcessor)
};
