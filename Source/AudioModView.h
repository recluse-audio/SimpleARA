/*
  ==============================================================================

    AudioModView.h
    Created: 20 Nov 2022 3:24:56pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ARAViewSection;
class ARA_AudioMod;
//==============================================================================
/*
*/
class AudioModView  : public juce::Component
{
public:
	AudioModView(ARAViewSection& section, ARA_AudioMod& mod);
    ~AudioModView() override;

    void paint (juce::Graphics&) override;
    void resized() override;
	
	void mouseEnter(const juce::MouseEvent& e) override;
	void mouseExit(const juce::MouseEvent& e) override;

private:
	juce::StringRef _getARAObjectAddressStrings();

	ARA_AudioMod& audioMod;
    ARAViewSection& araSection;
    
	void _drawAudioMod(juce::Graphics& g);
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioModView)
};
