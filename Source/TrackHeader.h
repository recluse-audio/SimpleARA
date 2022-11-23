/*
  ==============================================================================

    TrackHeader.h
    Created: 1 Nov 2022 12:48:57pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TrackHeader : public juce::Component
{
public:
	explicit TrackHeader (const juce::ARARegionSequence& regionSequenceIn);
	
	void resized() override;
	void paint (juce::Graphics& g) override;
	
private:
	void update();

    const juce::ARARegionSequence& regionSequence;
	juce::Label trackNameLabel;
};
