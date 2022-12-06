/*
  ==============================================================================

    ARAHelper_AudioMod.h
    Created: 20 Nov 2022 12:07:56pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ARA_AudioMod : public juce::ARAAudioModification
{
public:
	ARA_AudioMod(juce::ARAAudioSource* audioSource,
					   ARA::ARAAudioModificationHostRef hostRef,
					   const juce::ARAAudioModification* optionalModificationToClone);
	~ARA_AudioMod() override;
	
	void generateRandomColor();
	juce::Colour getColor() const;
private:
    juce::AudioProcessorValueTreeState  valueTree;
	juce::Colour modColor;
};
