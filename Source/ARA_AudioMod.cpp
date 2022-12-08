/*
  ==============================================================================

    ARAHelper_AudioMod.cpp
    Created: 20 Nov 2022 12:07:56pm
    Author:  Ryan Devens

  ==============================================================================
*/

#include "ARA_AudioMod.h"

ARA_AudioMod::ARA_AudioMod(juce::ARAAudioSource* audioSource, ARA::ARAAudioModificationHostRef hostRef, const juce::ARAAudioModification* optionalModificationToClone) : juce::ARAAudioModification(audioSource, hostRef, optionalModificationToClone)
{
	generateRandomColor();
    
    valueTree = std::make_unique<juce::ValueTree>("Audio Modification");
    gain = std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", juce::NormalisableRange<float>(0.f, 1.f, 0.01f), 0.5f);
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

