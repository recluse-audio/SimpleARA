/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleARAProcessor::SimpleARAProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ) //, valueTreeState(*this, nullptr, "PARAMETERS", this->_getParameterLayout())
#endif
{
    //valueTreeState.state.addListener(this);
    
}

SimpleARAProcessor::~SimpleARAProcessor()
{
   // valueTreeState.state.removeListener(this);
}

//==============================================================================
const juce::String SimpleARAProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleARAProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleARAProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleARAProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleARAProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleARAProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleARAProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleARAProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleARAProcessor::getProgramName (int index)
{
    return {};
}

void SimpleARAProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SimpleARAProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	playHeadState.isPlaying.store (false);
	prepareToPlayForARA (sampleRate, samplesPerBlock, getMainBusNumOutputChannels(), getProcessingPrecision());
}

void SimpleARAProcessor::releaseResources()
{
	playHeadState.isPlaying.store (false);
	releaseResourcesForARA();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleARAProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleARAProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	ignoreUnused (midiMessages);

	ScopedNoDenormals noDenormals;

	auto* audioPlayHead = getPlayHead();
	playHeadState.update (audioPlayHead);

//    if(valueTreeHasChanged)
//        _updateParameters();
	bool processARASuccess = processBlockForARA (buffer, isRealtime(), audioPlayHead);
	
	if (!processARASuccess )
		processBlockBypassed (buffer, midiMessages);
}

//==============================================================================
bool SimpleARAProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleARAProcessor::createEditor()
{
    return new SimpleARAEditor (*this);
}

//==============================================================================
void SimpleARAProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleARAProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleARAProcessor();
}


//juce::AudioProcessorValueTreeState::ParameterLayout SimpleARAProcessor::_getParameterLayout()
//{
//    std::vector<std::unique_ptr<RangedAudioParameter>> params;
//    
//    params.push_back (std::make_unique<AudioParameterFloat>("FOCUS VIEW", "Focus View", 0.0f, 2.0f, 1.f));
//    params.push_back (std::make_unique<AudioParameterFloat>("GAIN", "Gain", 0.0f, 1.0f, 0.01f));
////    params.push_back (std::make_unique<AudioParameterFloat>("ATTACK", "Attack", 0.0f, 2.0f, 0.01f));
////    params.push_back (std::make_unique<AudioParameterFloat>("DECAY", "Decay", 0.0f, 2.0f, 2.0f));
////    params.push_back (std::make_unique<AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f));
////    params.push_back (std::make_unique<AudioParameterFloat>("RELEASE", "Release", 0.0f, 2.0f, 0.1f));
//    
//    return { params.begin(), params.end() };
//}
//
//
//void SimpleARAProcessor::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged,
//                                                  const juce::Identifier &property)
//{
//    valueTreeHasChanged = true;
//}
//
//void SimpleARAProcessor::_updateParameters()
//{
//    
//}
//
//juce::AudioProcessorValueTreeState& SimpleARAProcessor::getValueTreeState()
//{
//    return valueTreeState;
//}
