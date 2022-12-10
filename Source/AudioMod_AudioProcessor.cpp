/*
  ==============================================================================

    AudioMod_AudioProcessor.cpp
    Created: 10 Dec 2022 1:53:14pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "AudioMod_AudioProcessor.h"

//=======================
AudioMod_AudioProcessor::AudioMod_AudioProcessor() :
valueTreeState(*this, nullptr, "Audio Modification Value Tree", this->_createParameterLayout())
{
    valueTreeState.state.addListener(this);
}

//=======================
AudioMod_AudioProcessor::~AudioMod_AudioProcessor()
{
    valueTreeState.state.addListener(this);
}


//=======================
void AudioMod_AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    mSampleRate = sampleRate;
}

//=======================
void AudioMod_AudioProcessor::releaseResources()
{
    
}

//=======================
void AudioMod_AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer)
{
    
}

//=======================
void AudioMod_AudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    
}

//=======================
void AudioMod_AudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    
}

//========================
juce::AudioProcessorValueTreeState& AudioMod_AudioProcessor::_getValueTreeState()
{
    return valueTreeState;
}

//========================
juce::AudioProcessorValueTreeState::ParameterLayout AudioMod_AudioProcessor::_createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    params.push_back (std::make_unique<AudioParameterFloat>("FOCUS VIEW", "Focus View", 0.0f, 2.0f, 1.f));
    params.push_back (std::make_unique<AudioParameterFloat>("GAIN", "GAIN", 0.0f, 1.0f, 0.01f));
//    params.push_back (std::make_unique<AudioParameterFloat>("ATTACK", "Attack", 0.0f, 2.0f, 0.01f));
//    params.push_back (std::make_unique<AudioParameterFloat>("DECAY", "Decay", 0.0f, 2.0f, 2.0f));
//    params.push_back (std::make_unique<AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f));
//    params.push_back (std::make_unique<AudioParameterFloat>("RELEASE", "Release", 0.0f, 2.0f, 0.1f));
    
    return { params.begin(), params.end() };
}

//==========================
void AudioMod_AudioProcessor::valueTreePropertyChanged(juce::ValueTree& tree, const juce::Identifier& property)
{
    
}
