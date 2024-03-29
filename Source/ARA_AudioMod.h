/*
  ==============================================================================

    ARAHelper_AudioMod.h
    Created: 20 Nov 2022 12:07:56pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioMod_AudioProcessor.h"

class ARA_AudioMod : public juce::ARAAudioModification
, private AudioMod_AudioProcessor
{
public:
	ARA_AudioMod(juce::ARAAudioSource* audioSource, ARA::ARAAudioModificationHostRef hostRef, const juce::ARAAudioModification* optionalModificationToClone, juce::UndoManager& undoManager);
    
	~ARA_AudioMod() override;
	
	void generateRandomColor();
	juce::Colour getColor() const;
    
    juce::AudioProcessorValueTreeState& getValueTreeState();

    float getParameterValue(juce::Identifier paramID) const;
	
	void setSelected(bool shouldBeSelected);
	
private:
	juce::Colour modColor;
	
	bool currentlySelected = false;

};
