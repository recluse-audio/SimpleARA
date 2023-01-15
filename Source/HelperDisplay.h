/*
  ==============================================================================

    HelperDisplay.h
    Created: 23 Nov 2022 4:31:26pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ARA_PlaybackRegion;
class ARA_AudioMod;
//==============================================================================
/**
	A class that takes ARA objects and displays relevant info on a label as a string
*/
class HelperDisplay  : public juce::Component
{
public:
    HelperDisplay();
    ~HelperDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

	void clearDisplay();
	void displayPlaybackRegion(const ARA_PlaybackRegion& pRegion);
    void displayAudioMod(const ARA_AudioMod& pMod);
private:
	std::unique_ptr<juce::Label> displayLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelperDisplay)
};
