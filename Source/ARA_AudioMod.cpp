/*
  ==============================================================================

    ARAHelper_AudioMod.cpp
    Created: 20 Nov 2022 12:07:56pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "ARA_AudioMod.h"

ARA_AudioMod::ARA_AudioMod(juce::ARAAudioSource* audioSource, ARA::ARAAudioModificationHostRef hostRef,
                           const juce::ARAAudioModification* optionalModificationToClone, juce::UndoManager& undoManager)
:   juce::ARAAudioModification(audioSource, hostRef, optionalModificationToClone)
,   AudioMod_AudioProcessor(undoManager)

{
    
	generateRandomColor();
    
}

ARA_AudioMod::~ARA_AudioMod()
{
	
}

void ARA_AudioMod::generateRandomColor()
{
	auto randomValue = juce::Random();
	juce::uint8 r = randomValue.nextInt(255);
	juce::uint8 g = randomValue.nextInt(255);
	juce::uint8 b = randomValue.nextInt(255);

	modColor = {r, g, b};
}

juce::Colour ARA_AudioMod::getColor() const
{
	return modColor;
}

//====================================
juce::AudioProcessorValueTreeState& ARA_AudioMod::getValueTreeState()
{
    return this->_getValueTreeState();
}

//====================================
float ARA_AudioMod::getParameterValue(juce::Identifier paramID) const
{
    return valueTreeState.getRawParameterValue(paramID)->load();
}
